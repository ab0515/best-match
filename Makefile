CC = gcc
CFLAGS = -Wall -std=c99

all: questions qtree cat

questions:
	$(CC) $(CFLAGS) questions.c test1.c -o test1
qtree:
	$(CC) $(CFLAGS) questions.c qtree.c test2.c -o test2
cat:
	$(CC) $(CFLAGS) questions.c qtree.c categorizer.c -o categorizer
clean:  
	rm test1 test2 categorizer
