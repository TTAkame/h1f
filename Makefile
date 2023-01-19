CC = g++ -std=c++17
CFLAGS = -g -Wall -Werror


TARGET = SearchNewBooks
all:	$(TARGET)

read.o: read.cpp
	$(CC) -c $(CFLAGS) read.cpp

SearchNewBooks:	read.o
	$(CC) $(CFLAGS) -o $(TARGET) read.o

clean:
	rm -rf *.o $(TARGET)