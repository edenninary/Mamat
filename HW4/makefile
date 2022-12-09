#Parameters
CC     = gcc
CCLINK = $(CC)
CFLAGS = -Wall -g -std=c99


libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.
	
grades.o: grades.c grades.h linked-list.h
	$(CC) $(CFLAGS) -c -fpic grades.c

clean:
	rm -f libgrades.so grades.o
