#include <errno.h>
#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "AudioReader.h"
#include "FFT.h"

int main(){
    int number = 0;
    char* s;
    printf("Choose audio file: ");
    scanf("%d", &number);

    switch (number) {
        case 1:
        s = "sound/M1F1-uint8-AFsp.wav";
        break;
        case 2:
        s = "sound/music-sample-44100hz-16bit.wav";
        break;
        case 3:
        s = "sound/tone_440.wav";
        break;
    }

    const char *filename = s;
    FILE* fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        printf("Audio file could not be opended %s\n", strerror(errno));
        return -1;
    }

    struct AudioFile audio;
    if (!readWaveFile(fptr, &audio)) {
        return -1;
    }
    
    //printMeta(&audio.metadata);
    //printSamples(audio.samples, audio.metadata.sampleCount, 100);

    dft(1024, audio.samples, audio.metadata.sampleCount, audio.metadata.sampleRate);
    //float samples[] = {1,0,-1,0,1,0,-1,0};
    //int sampleSize = sizeof(samples) / sizeof(samples[0]);

    //dft(8, samples, sampleSize, 8000);

    return 0;
}