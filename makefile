CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
EXEC=libgrades.so
RM=rm -rf

#exe file
libgrades.so: grades.o
	$(CC) -shared grades.o -o libgrades.so -llinked-list -L.
#object files
grades.o: grades.c grades.h
	$(CC)  $(CFLAGS) -c -fpic grades.c -o grades.o




#cleanup
clean:
	$(RM) *.o $(EXEC)




