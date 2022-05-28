/* Auteur : MABROUK Fayez
 *Création : 24-03-2022
 *Modification : 06-04-2022*/

#include <stdio.h>
#include <stdlib.h>
#include "TP8.h"

void affiche_tab(int *tab) {
    int i;
    for(i = 0; i < NBLETTRES; ++i){
        printf("tab[%d] = %d\n", i, tab[i]);
    }
    printf("\n");
}

int* stockeOccurrences(FILE* in, int tab[NBLETTRES]){
    int i;
    int nb;
    char c;
    for(i = 0; i < NBLETTRES; i++){
        tab[i] == 0;
    }
    while((c = fgetc(in)) != EOF){
        tab[c] ++;
    }
    return tab;
}

int compteLettres(int tab[]) {
    int i,nb;
    nb = 0;
    for(i = 0; i < NBLETTRES; i++){
        if(tab[i] != 0)
            nb++;
    }
    return nb;
}



Huffman initHuffman(int tab[], int len) {
    
    Huffman tmp;
    int i,cmpt;
    tmp.array = (Noeud*)malloc(sizeof(Noeud)*(2*len-1));
    
    /*
    if( NULL == tmp){
        
        fprintf(stderr, "Erreur d'allocations");
        
        exit(1);
    }
    */
    cmpt = 0;
    for(i = 0; i < NBLETTRES; i++ ){
        if(0 != tab[i]){   
            tmp.array[cmpt].lettre = i;
            tmp.array[cmpt].occur = tab[i];
            tmp.array[cmpt].fd = -1;
            tmp.array[cmpt].fg = -1;
            cmpt ++;
        }
    }
    tmp.nbLeaves =len ;
    tmp.nbNodes = len;
    tmp.nextLeaf = 0 ;
    tmp.nextInternal = len;

    return tmp;
}

void affiche_huff(Huffman * huff) {
    int i;
    printf("\n__________________________________");
    printf("\nlettre ");
    for (i = 0; i< huff->nbNodes;i++)
        printf("%2c ",huff->array[i].lettre);
    printf("\n__________________________________");
    printf("\noccur  ");
    
    for(i = 0; i< huff->nbNodes;i++)
        printf("%2d ",huff->array[i].occur);
    printf("\n__________________________________");
    printf("\nfg      ");
    for(i = 0; i< huff->nbNodes;i++)
        printf("%2d ",huff->array[i].fg);
    printf("\n__________________________________");
    printf("\nfd      ");
    for(i = 0; i< huff->nbNodes;i++)
        printf("%2d ",huff->array[i].fd);
    printf("\n__________________________________");
    printf("\nindice  ");
    for(i = 0; i< huff->nbNodes;i++)
        printf("%2d ",i);
    printf("\n__________________________________");
    
    printf("\n");
}

int compare(const void *p1, const void *p2) {
    Noeud e1 = *((Noeud *) p1);
    Noeud e2 = *((Noeud* ) p2);
    if (e1.occur < e2.occur)
        return 0;
    else if (e1.occur == e2.occur) {
        if (e1.lettre > e2.lettre)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

void tri(Noeud* array, int len) {
    qsort(array, len, sizeof(Noeud), compare);
}

int minNode(Huffman* huff) {

    int min;
    if(huff->nbLeaves == huff->nbNodes) {
        min = huff->nextLeaf;
        huff->nextLeaf++;
        return min;
    } else if ((huff->nbLeaves != huff->nextLeaf) && (huff->array[huff->nextLeaf].occur <= huff->array[huff->nextInternal].occur)) {
        min = huff->nextLeaf;
        huff->nextLeaf++;
        return min;
    } else {
        min = huff->nextInternal;
        huff->nextInternal++;
        return min;
    }
}


void augmenteArbre(Huffman* huff) {
    int i1, i2;
    while (huff->nbNodes != (huff->nbLeaves)*2 -1){
        i1 = minNode(huff);
        i2 = minNode(huff);
        huff->array[huff->nbNodes].occur = huff->array[i1].occur + huff->array[i2].occur;
        huff->array[huff->nbNodes].fg = i1;
        huff->array[huff->nbNodes].fd = i2;
        huff->array[huff->nbNodes].lettre = '?';
        huff->nbNodes++;
    }
}

Huffman huffmanTree(FILE* in) {
    
    Huffman huff;
    int *tmp;
    tmp = (int*)malloc(sizeof(int)* NBLETTRES);
    if (NULL == tmp){
        fprintf(stderr, "Erreur d'allocations");
        exit(1) ;
    }

    tmp = stockeOccurrences(in, tmp );
    huff = initHuffman(tmp,compteLettres(tmp));
    tri(huff.array,compteLettres(tmp));
    augmenteArbre(&huff);
    affiche_huff(&huff);
    return huff;
}

void encodage(Huffman *huff, Noeud *racine, unsigned char lettre, char mot[], char code[], int indice) {
    if (racine -> fg == -1 && racine -> fd == -1) {
        if (racine -> lettre == lettre) {
            mot[indice] = '\0';
            strcpy(code, mot);
        }
        return;
    }
    mot[indice] = '0';
    encodage(huff, &huff->array[racine->fg], lettre, mot, code, indice+1);
    mot[indice] = '1';
    encodage(huff, &huff->array[racine->fd], lettre, mot, code, indice+1);
}

char ** construitCode(Huffman huff) {
    char **traduc;
    int i;
    char mot[100] = {};
    char code[100] = {};
    traduc = (char **) malloc(sizeof(char *) * NBLETTRES);
    if (!traduc) {
        fprintf(stderr, "Erreur d'allocation construitCode\n");
        return NULL;
    }
    for (i = 0; i < NBLETTRES; i++)
        traduc[i] = NULL;
    for (i = 0; i < huff.nbLeaves; i++) {
        mot[0] = 0;
        encodage(&huff, &huff.array[huff.nbNodes - 1], huff.array[i].lettre, mot, code, 0);
        traduc[huff.array[i].lettre] = (char *) malloc(sizeof(char) * strlen(code) + 1);
        if (!traduc[huff.array[i].lettre]) {
            fprintf(stderr, "Erreur d'allocation construitCode\n");
            return NULL;
        }
        strcpy(traduc[huff.array[i].lettre], code);
    }
    /* affiche code */
    for (i = 0; i < NBLETTRES; i++) {
        if (traduc[i] != NULL)
            printf("%c : %s\n", i, traduc[i]);
    }
    return traduc;
}
