#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "FFT.h"
#include "kissFFT/kiss_fft.h"
#include "kissFFT/kiss_fftr.h"




void fft(float* bin, int N, float* ampArr){
    kiss_fftr_cfg cfg = kiss_fftr_alloc(N, 0, NULL, NULL);
    kiss_fft_cpx *cpx = malloc(N/2 + 1 * sizeof(kiss_fft_cpx));

    printf("FFT is running\n");
    kiss_fftr(cfg, bin, cpx);

    // for (int i = 0; i < 10; i++) {
    //     printf("Real %f ", cpx[i].r);
    //     printf("Img %f", cpx[i].i);
    //     printf("\n");
    // }

    for (int i = 0; i < ((N/2) + 1); i++) {
        ampArr[i] = 10.0 * log10f(pow(cpx[i].r, 2) + pow(cpx[i].i, 2)); //20.0 * log10f( sqrtf(pow(cpx[i].r, 2) + pow(cpx[i].i, 2)) );

        // if (i < 10) {
        //     printf("sqrt{%f ^2 + %f ^2} = %f \n", cpx[i].r, cpx[i].i, ampArr[i]);
        // }
    }
    kiss_fftr_free(cfg);
}





























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

/*I will continue to implement this later but for now I will use kissFFT*/



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