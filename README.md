# Sectrum Analyzer
This is a summer project where I will develop a spectrum analyzer.

Currently you can read a WAVE file and get the meta data printed. You will also recieve a float* with the normalized values of the audio samples.

## Support
The WAV reader currently supports PCM WAV files with 8-bit unsigned or 16-bit signed samples. Stereo data is kept interleaved. The program validates RIFF/WAVE identifiers, audio format, bit depth, and basic metadata consistency before reading samples.

## TODO
FFT, playback and visuals