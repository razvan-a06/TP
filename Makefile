CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = hangman
OBJS = main.o functii.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c functii.h
	$(CC) $(CFLAGS) -c main.c

functii.o: functii.c functii.h
	$(CC) $(CFLAGS) -c functii.c

clean:
	rm -f $(OBJS) $(TARGET)