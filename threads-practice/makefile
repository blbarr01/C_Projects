# my template makefile 
# refer to https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 
# for more detailed info on how makefiles work 


# variables to set compiler, flags 
# objs and dependant .h files
CC=gcc
CFLAGS=-I. -g -pthread
OBJ = threads.o 


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# a utility function to clear up obj files

# all object files are compiled into an executable called main
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	./main
.PHONY: clean

clean: 
	rm -f *.o
