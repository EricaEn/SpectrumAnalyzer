# Spectrum Analyzer

This is a learning project where I am building a spectrum analyzer in C.

I am building the project step by step to learn how audio analysis works, starting with WAV parsing and PCM samples, then moving on to DFT/FFT, amplitude calculation, playback, and visualization.

Currently I'm using the kissFFT library for FFT but the intention is to implement my own algorithm later.

## Current status

The program can currently:

* Read PCM WAV files
* Parse and print WAV metadata
* Locate the `data` chunk, including files with extra chunks before it
* Normalize audio samples into floating-point values
* Run a naive DFT on a block of samples
* Print real part, imaginary part, magnitude, and frequency bin information
* Detect the dominant frequency bin in a known test signal
* Calculate the amplitude in decibel in a block of N samples using the kissFFT algorithm



## WAV support

The WAV reader currently supports PCM WAV files with:

* 8-bit unsigned samples
* 16-bit signed samples
* Mono or stereo audio

Stereo data is currently kept interleaved.

The program validates:

* RIFF/WAVE identifiers
* Audio format
* Bit depth
* Basic metadata consistency
* Chunk layout before reading sample data

## DFT support

The project currently includes a naive DFT implementation.

For each bin `k`, the DFT compares the input block with a complex sinusoid. The bin frequency is calculated as:

```text
bin_freq = k * sample_rate / N
```

where:

* `k` is the frequency bin index
* `sample_rate` is the WAV file sample rate
* `N` is the block size used for the DFT

For real-valued audio input, only bins `0..N/2` are needed for a magnitude spectrum. The upper half of the DFT result represents mirrored negative-frequency information.

## FFT implementation

Currently ([kissFFT](https://github.com/mborgerding/kissfft)) is used for the FFT calculations. The intention is to implement my own algorithm of FFT later in the project.

## TODO

Planned next steps:


* Add window functions (Hanning window)
* Add audio playback
* Add real-time audio input
* Add visualization
* Explore SDL2 for rendering
* Explore PortAudio for audio callbacks
* Add a ring buffer for real-time processing

## Notes

This project is mainly a learning project. The first implementation prioritizes clarity and understanding over performance.
