# my template makefile 
# refer to https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/ 
# for more detailed info on how makefiles work 


# variables to set compiler, flags 
# objs and dependant .h files
CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = main.o  


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# a utility function to clear up obj files

# all object files are compiled into an executable called main
main.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	./main.exe

.PHONY: clean

clean: 
	rm -f *.o
