#include <errno.h>
#include <complex.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "AudioReader.h"

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
    
    printMeta(&audio.metadata);

    return 0;
}