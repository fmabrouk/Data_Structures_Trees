CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=main.o TP8.o 

TP8 : $(OBJ) 
	$(CC)  -o $@ $^ $(CFALGS) $(LDFLAGS)
main.o: main.c TP8.h 
	$(CC)  -c $< $(CFALGS)
TP8.o: TP8.c TP8.h 
	$(CC)  -c $< $(CFALGS)
clean:
	rm-f*.o