CC=gcc
CFLAGS=-ansi -pedantic -Wall -g
OBJ=correcteur_2.o Listes.o ArbreBK.o Levenshtein.o

correcteur_2 : $(OBJ) 
	$(CC)  -o $@ $^ $(CFALGS) 
correcteur_2.o:correcteur_2.c Listes.h ArbreBK.h Levenshtein.h
	$(CC)  -c $< $(CFALGS)
Listes.o: Listes.c Listes.h 
	$(CC)  -c $< $(CFALGS)
ArbreBK.o:ArbreBK.c  ArbreBK.h
	$(CC)  -c $< $(CFALGS)
Levenshtein.o:Levenshtein.c  Levenshtein.h
	$(CC)  -c $< $(CFALGS)
clean:
	rm-f*.o
