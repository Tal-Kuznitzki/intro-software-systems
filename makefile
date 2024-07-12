CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
OBJS=main.o stack.o student.o
EXEC=prog.exe
RM=rm -rf

#exe file
$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

#object files
main.o: main.c stack.h student.h common.h 
	$(CC) $(CFLAGS) -c main.c
stack.o: stack.c stack.h common.h
	$(CC) $(CFLAGS) -c stack.c
student.o: student.c student.h common.h
	$(CC) $(CFLAGS) -c student.c

#cleanup
clean:
	$(RM) *.o $(EXEC)
