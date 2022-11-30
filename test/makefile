# my template makefile 
# refer to https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 
# for more detailed info on how makefiles work 


# variables to set compiler, flags 
# objs and dependant .h files
CC=gcc
CFLAGS=-I.
DEPS = queue.h schedules.h process.h stack.h
OBJ = main.o queue.o schedules.o process.o stack.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# a utility function to clear up obj files

# all object files are compiled into an executable called assignemnt-02.exe
assignment-02.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean
clean: 
	rm -f *.o
