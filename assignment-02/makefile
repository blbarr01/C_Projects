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



# all object files are compiled into an executable called assignemnt-02.exe
assignment-02.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	rm -f *.o
# a utility function to clear up obj files
# run "make clean" 
.PHONY: clean
clean: 
	rm -f *.o 
	rm assignment-02.exe