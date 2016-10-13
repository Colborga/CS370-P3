CC = gcc
INCLUDE= -g -Wall

all: PA2

PA2: Initiator.o Mean.o Median.o Mode.o
	$(CC) Initiator.o -o PA2
	$(CC) Mean.o -o Mean
	$(CC) Median.o -o Median
	$(CC) Mode.o -o Mode

Main: Main.o
	$(CC) Main.o -o PA2

Main.o: Main.c
	$(CC) $(INCLUDE) -c Main.c

Mean: Mean.o
	$(CC) Mean.o -o Mean

Mean.o: Mean.c
	$(CC) $(INCLUDE) -c Mean.c

Median: Median.o
	$(CC) Median.o -o Median

Median.o: Median.c
	$(CC) $(INCLUDE) -c Median.c

Mode: Mode.o
	$(CC) Mode.o -o Mode
Mode.o: Mode.c
	$(CC) $(INCLUDE) -c Mode.c

clean:
	rm -rf *.o Mean Median Mode PA2
