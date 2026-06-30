# Spectrum Analyzer

This is a summer learning project where I am building a spectrum analyzer in C.

I am building the project step by step to learn how audio analysis works, starting with WAV parsing and PCM samples, then moving on to DFT/FFT, amplitude calculation, playback, and visualization.

## Current status

The program can currently:

* Read PCM WAV files
* Parse and print WAV metadata
* Locate the `data` chunk, including files with extra chunks before it
* Normalize audio samples into floating-point values
* Run a naive DFT on a block of samples
* Print real part, imaginary part, magnitude, and frequency bin information
* Detect the dominant frequency bin in a known test signal

A 440 Hz sine wave test file was used to verify the DFT implementation. With a sample rate of 44100 Hz and a block size of 1024 samples, the expected bin is:

```text
k ≈ 440 * 1024 / 44100 ≈ 10.22
```

The largest magnitude appears at bin 10, which confirms that the DFT finds the expected frequency region.

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

## TODO

Planned next steps:

* Improve amplitude scaling
* Add window functions
* Implement FFT
* Add audio playback
* Add real-time audio input
* Add visualization
* Explore SDL2 for rendering
* Explore PortAudio for audio callbacks
* Add a ring buffer for real-time processing

## Notes

This project is mainly a learning project. The first implementation prioritizes clarity and understanding over performance.
