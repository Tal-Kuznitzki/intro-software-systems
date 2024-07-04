CC= gcc
CFLAGS= $ (CC)
CCLINK= -g -Wall -std=c99
OBJS= main.o stack.o student.o
EXEC = main.exe
RM= -rf *.o *.exe

#exe file
$(EXEC) : $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

#object files
main.o : main.c stack.h student.h common.h
	$(CC) $(CCLINK) -c main.c
stack.o : stack.c stack.h common.h
	$(CC) $(CCLINK) -c stack.c
student.o : student.c student.h common.h
	$(CC) $(CCLINK) -c student.c

#cleanup
clean:
	$(RM)