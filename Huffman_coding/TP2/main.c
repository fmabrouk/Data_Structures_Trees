/* Auteur : MABROUK Fayez
 *Création : 24-03-2022
 *Modification : 06-04-2022*/


#include "TP8.h"
#include <stdio.h>
#include <stdlib.h>

/*Pour compiler le programme :
fayez@fayez-IdeaPad-3-14ADA05:~$ make
fayez@fayez-IdeaPad-3-14ADA05:~$ ./TP8 texte.txt
*/

int main(int argc,char * argv[]) {

   
   FILE * fichier;
    Huffman  huff;
    char mot[NBLETTRES];
    char  code[NBLETTRES];
    int indice ;
    indice = 0;
    char **tab;
    
    fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        fprintf(stderr, "Pas de fichier texte en argument\n");
        exit(1);
    }
    huff = huffmanTree(fichier);
    encodage(&huff,huff.array,huff.array->lettre,mot,code,indice);
    tab = construitCode(huff);
    fclose(fichier);
    return 0;
}
