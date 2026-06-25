#include <complex.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "AudioReader.h"

/*
Checks if the buffer at position i contains a target string such as "RIFF" or "WAVE"
*/
bool checkAudioFile (uint8_t *buffer, int i, char* target){
    int k = 0;
    char* word = malloc(4 * sizeof(char) + 1);
    if (word == NULL) {
        printf("Allocating memory failed %s\n", strerror(errno));
        return false;
    }
    
    for (int j = i; i < j+4; i++) {
        word[k++] = (char)buffer[i];
    }
    int res = strcmp(target, word);

    free(word);
    return res == 0;
}

/*
Reads the data from the "fmt "-chunk and adds it to the WavMetadata-struct
*/
void readMeta(uint8_t *buffer, int i, struct WavMetadata *data){
    uint32_t fs = 0;
    int shift = 0;
    for (int j = i; i < j+2; i++) {
        fs |= buffer[i]<< shift;
        shift += 8;
    }
    data->audioFormat = fs;

    fs = 0; 
    shift = 0;
    for (int j = i; i < j+2; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }
    data->channels = fs;

    fs = 0;
    shift = 0;
    for (int j = i; i < j+4; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }
    data->sampleRate = fs;

    fs = 0;
    shift = 0;
    for (int j = i; i < j+4; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }
    data->byteRate = fs;

    fs = 0;
    shift = 0;
    for (int j = i; i < j+2; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }
    data->blockAlign = fs;

    fs = 0;
    shift = 0;
    for (int j = i; i < j+2; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }
    data->bitsPerSample = fs;
}

/*
Prints the meta data retrieved from the "fmt "-chunk
*/
void printMeta(struct WavMetadata *data){
    printf("Audio format: %d\n", data->audioFormat);
    printf("Number of channels: %d\n", data->channels);
    printf("Sample rate: %d\n", data->sampleRate);
    printf("Byte rate: %d\n", data->byteRate);
    printf("Block align: %d\n", data->blockAlign);
    printf("Bits per sample: %d\n", data->bitsPerSample);
}

/*
Finds the max and the min float number in the buffer and prints out the first number of samples provided
*/
void printSamples(float *buffer, int bufferSize, int numberOfSamples){
    if (bufferSize < numberOfSamples) {
        numberOfSamples = bufferSize;
    }

    float max = buffer[0];
    float min = max;
    for (int i=1; i<bufferSize; i++) {
        if (i < numberOfSamples) {
            printf("Sample %d: %f\n", i, buffer[i]);
        }
        if (buffer[i] > max) {
            max = buffer[i];
        } else if (buffer[i] < min) {
            min = buffer[i];
        }
    }

    printf("Max: %f\n", max);
    printf("Min: %f\n", min);
}

/*
Normalizes the 16 bit signed integer values to float values
*/
float* buffer16Bit(int i, uint8_t *buffer, struct WavMetadata *data){
    float *normBuffer = malloc(data->dataSize/2 * sizeof(float));
    if (normBuffer == NULL) {
        printf("Allocating memory failed %s\n", strerror(errno));
        return NULL;
    }
    int j = 0;
    for (int k = i; i < (k + data->dataSize); i+=2) {
        int16_t temp = buffer[i];
        temp |= buffer[i+1] << 8;
        normBuffer[j++] = temp / 32768.0;
    }

    return normBuffer;
}

/*
Normalizes the 8 bit unsigned integer values to floas values
*/
float* buffer8Bit(int i, uint8_t *buffer, struct WavMetadata *data){
    float *normBuffer = malloc(data->sampleCount * sizeof(float));
    if (normBuffer == NULL) {
        printf("Allocating memory failed %s\n", strerror(errno));
        return NULL;
    }
    int j = 0;
    for (int k = i; i < (k + data->dataSize); i++) {
        uint8_t temp = buffer[i];
        normBuffer[j++] = (temp-128) / 128.0;
    }

    return normBuffer;
}

/*
Reads the data-chunk and checks if the audio is in 16bit or 8 bit per sample. Then Normalizes it and returns a float* with normalized values
*/
float* toBuffer(struct WavMetadata *data, int i, uint8_t *buffer){
    int fs = 0;
    int shift = 0;
    for (int j = i; i < j+4; i++) { 
        fs |= buffer[i]<< shift; 
        shift += 8;
    }

    int dataSize = fs;
    data->dataSize = dataSize;
    data->bytesPerSample = data->bitsPerSample / 8;
    data->sampleCount = dataSize / data->bytesPerSample;
    data->frameCount = dataSize / data->blockAlign;

    if (data->bitsPerSample == 16) { 
        return buffer16Bit(i, buffer, data);
    
    } else if (data->bitsPerSample == 8) {
        return buffer8Bit(i, buffer, data);
    } else {
        printf("Bit depth is not supported\n");
        return NULL;
    }
}

/*
Checks if the audio file contains the required chunks "RIFF", "WAVE", "fmt ", den reads the meta data from the "fmt "-chunk
*/
bool AFCheck(uint8_t *buffer, long file_size, struct WavMetadata *data){
    if ((!checkAudioFile(buffer, 0, "RIFF")) || (!checkAudioFile(buffer, 8, "WAVE")) || (!checkAudioFile(buffer, 12, "fmt "))) {
        printf("File is not a valid wave file.\n");
        return false;
    }

    for (int i = 12; i < file_size; i++) { 
        if ((buffer[i] == 0x66) && (buffer[i+1] == 0x6D) && (buffer[i+2] == 0x74) && (buffer[i+3] == 0x20)) { //searches for "fmt "
            readMeta(buffer, i+8, data);
        } 
    }
    printf("\n");


    if (data->audioFormat != 1) {
        printf("Audio format is not supported\n");
        return false;
    }  if ((data->channels != 1) && (data->channels != 2)) {
        printf("Number of channels is not supported\n");
        return false;
    }
    return true;
}

/*
Read the audio file from the file pointer. From the file, meta data is extracted and the sample content is normalized to float*.
*/
bool readWaveFile(FILE* fptr, struct AudioFile *audio){
    fseek(fptr, 0, SEEK_END);
    long file_size = ftell(fptr);
    rewind(fptr);

    uint8_t *buffer = malloc(file_size);
    if (buffer == NULL) {
        printf("Allocating memory failed %s\n", strerror(errno));
    }

    fread(buffer, sizeof(char),file_size, fptr);
    fclose(fptr);

    if (!AFCheck(buffer, file_size, &audio->metadata)) {
        return false;
    }
    
    bool found = false;
    for (int i = 12; i< file_size; i++) {
        if ((buffer[i] == 0x64) && (buffer[i+1] == 0x61) && (buffer[i+2] == 0x74) && (buffer[i+3] == 0x61)) {
            audio->samples = toBuffer(&audio->metadata, i+4, buffer);
            found = true;
        } 
    }
    printf("\n");
    if (!found) {
        printf("File is nog a valid wave-file, data chunk cannot be found\n");
        return false;
    }

    free(buffer);
    if (audio->samples == NULL) {
        printf("Something went wrong.\n");
        return false;
    }

    return true;
}