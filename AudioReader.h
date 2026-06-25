#include <complex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct WavMetadata {
    int audioFormat;
    int channels;
    int sampleRate;
    int byteRate;
    int blockAlign;
    int bitsPerSample;
    int bytesPerSample;
    int sampleCount;
    int frameCount;
    int dataSize;
};

struct AudioFile {
    struct WavMetadata metadata;
    float *samples;
};

bool readWaveFile(FILE* fptr, struct AudioFile *audio);
void printSamples(float *buffer, int bufferSize, int numberOfSamples);
void printMeta(struct WavMetadata *data);
