CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = main

SRC = main.c AudioReader.c
OBJ = main.o AudioReader.o
HEADERS = AudioReader.h

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