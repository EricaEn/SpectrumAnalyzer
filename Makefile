CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main

SRC = main.c AudioReader.c FFT.c kissFFT/kiss_fft.c kissFFT/kiss_fftr.c
OBJ = main.o AudioReader.o FFT.o kissFFT/kiss_fft.o kissFFT/kiss_fftr.o
HEADERS = AudioReader.h FFT.h

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c main.c

AudioReader.o: AudioReader.c AudioReader.h
	$(CC) $(CFLAGS) -c AudioReader.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ)