#include <math.h>
#include <stdio.h>

#include "FFT.h"

/*
FFT size = 0
FFT-storlek, ofta kallad N, är antalet samples du analyserar i ett FFT-block. FFT size är storleken på analysblocket, inte automatiskt samma sak som ljudkortets callback-buffer.
1024 / 44100 ≈ 0.0232 sekunder ≈ 23.2 ms
Bin bred: 44100 / 1024 ≈ 43.1 Hz

Seconds / N of samples = sampling interval
f_max = sample rate / 2 (Nyqvist)
*/


/*
bin_freq = k * sample_rate / N
k  →  antal perioder i blocket  →  frekvens i Hz
*/



int dft(int N, float *samples, int sampleSize, int sampleRate){
    int bins = ceil(N / 2) + 1;
    for (int k = 0; k < bins; k++) {
        double real = 0;
        double img = 0; 

        for (int n = 0; n < sampleSize; n++) {
            double angle = 2 * M_PI * k * n/N;

            real += samples[n] * cos(angle);
            img -= samples[n] * sin(angle);
        }

        double magnitude = sqrt(pow(real, 2) + pow(img, 2));
        double freq = k * sampleRate / N;

        printf("k = %d, freq = %f, real = %f, img = %f, magnitude = %f\n", k, freq, real, img, magnitude);
    }

    

    return 1;
}