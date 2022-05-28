/* Auteur : MABROUK Fayez
 *Création : 24-03-2022
 *Modification : 06-04-2022*/


#ifndef __TP8_H_
#define __TP8_H_


# define NBLETTRES 256
#include <stdio.h>

typedef struct {
    unsigned char lettre ;
    int occur ;
    int fg ;
    int fd ;
} Noeud ;

typedef struct {
    Noeud * array ;
    int nbLeaves ;
    int nbNodes ;
    int nextLeaf ;
    int nextInternal ;
} Huffman ;

/*
    BUT : fonction permet d'afficher un tableau.
    PARAM : tab de type int*.
*/
void affiche_tab(int *tab);

/*
    BUT : fonction permet de stocker les ASCII des lettres dans un tableau .
    PARAM : in de type FILE* et tab[NBLETTRES] de type int.
    RETURN : renvoie un tableau.
*/
int* stockeOccurrences(FILE* in, int tab[NBLETTRES]);

/*
    BUT : fonction permet de calculer le nombre d'occurences de chaque lettre dans tab.
    PARAM : tab[] de type int.
    RETURN : renvoie le nombre d'occurences.
*/
int compteLettres(int tab[]);

/*
    BUT : fonction permet le tableau huffman.
    PARAM : tab[] de type int et len de type int.
    RETURN : renvoie un tableau de type huffman.
*/
Huffman initHuffman(int tab[], int len);

/*
    BUT : fonction permet d'afficher un tableau de type huffman.
    PARAM : huff de type Huffman*.
*/
void affiche_huff(Huffman * huff);

/*
    BUT : fonction permet de comparer entre deux constantes.
    PARAM : p1 et p2 de type const*.
    RETURN : renvoie -1 si p1 est plus petit et 1 sinon.
*/
int compare(const void *p1, const void *p2);

/*
    BUT : fonction permet de trier le tableau huffman.
    PARAM : array de type Noeud* et len de type int.
*/
void tri(Noeud *array, int len) ;

/*
    BUT : fonction permet de renvoyer le minimum de noeuds.
    PARAM : huff de type Huffman*.
    RETURN : renvoie le minimum .
*/
int minNode(Huffman* huff);

/*
    BUT : fonction permet d'augmenter les indices de l'arbre de huffman.
    PARAM : huff de type Huffman*.
*/
void augmenteArbre(Huffman* huff);

/*
    BUT : fonction permet de renvoyer l'arbre huffman.
    PARAM : in de type FILE*.
    RETURN : huffman. 
*/
Huffman huffmanTree(FILE* in);

void encodage(Huffman *huff, Noeud *racine, unsigned char lettre, char mot[], char code[], int indice);
char ** construitCode(Huffman huff);
#endif
