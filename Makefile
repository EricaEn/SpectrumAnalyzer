CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main

SRC = main.c AudioReader.c FFT.c kissFFT/kiss_fft.c kissFFT/kiss_fftr.c Visualize.c
OBJ = main.o AudioReader.o FFT.o kissFFT/kiss_fft.o kissFFT/kiss_fftr.o Visualize.o
HEADERS = AudioReader.h FFT.h

CFLAGS += $(shell sdl2-config --cflags)
LDFLAGS += $(shell sdl2-config --libs)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

AudioReader.o: AudioReader.c AudioReader.h
	$(CC) $(CFLAGS) -c AudioReader.c

FFT.o: FFT.c FFT.h
	$(CC) $(CFLAGS) -c FFT.c

Visualize.o: Visualize.c Visualize.h
	$(CC) $(CFLAGS) -c Visualize.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)