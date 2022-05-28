CC=gcc
CFLAGS=-ansi -pedantic -Wall
OBJ=correcteur_0.o Listes.o ATR.o 

correcteur_0 : $(OBJ) 
	$(CC)  -o $@ $^ $(CFALGS) $(LDFLAGS)
correcteur_0.o:correcteur_0.c Listes.h ATR.h
	$(CC)  -c $< $(CFALGS)
Listes.o: Listes.c Listes.h 
	$(CC)  -c $< $(CFALGS)
ATR.o:ATR.c  ATR.h
	$(CC)  -c $< $(CFALGS)
clean:
	rm-f*.o