/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 30-03-2022
 *Modification : 02-04-2022*/

#include "Levenshtein.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int MAX(int a, int b) {
    int max = (a > b) ?  a :  b;
    return max;
}

int MIN(int a, int b) {
    int min = (a < b) ?  a:  b;
    return min;
}

int min_3_param(int a, int b, int c) {
    if ((a < b) && (a < c))
        return a;
    if ((b < a) && (b < c))
        return b;
    if ((c < a) && (c < b))
        return c;
}

char *chaine_supp_prem (char *chaine) {
    int taille;
    char *nouv_chaine = NULL;

    if (chaine != NULL) {
        taille = strlen(chaine) - 1;
        nouv_chaine = (char *)malloc(sizeof(char) * (taille) + 2);
        if (nouv_chaine != NULL)
            strcpy (nouv_chaine, chaine + 1);
            nouv_chaine[strlen(nouv_chaine) + 1]= '\0'; 
    }
    return nouv_chaine;
}

int Levenshtein(char * un, char * deux) {
    char * chaine1, *chaine2;
    int i, j, taille_un, taille_deux;

    taille_un = strlen(un);
    taille_deux = strlen(deux);
    chaine1 = chaine_supp_prem(un);
    chaine2 = chaine_supp_prem(deux);
    
    if(MIN(taille_un, taille_deux) == 0)
        return MAX(taille_un, taille_deux);
    else if(un[0] == deux[0])
        return Levenshtein(chaine1, chaine2);
    else {
        return 1 + min_3_param(Levenshtein(chaine1, deux),Levenshtein(un, chaine2),Levenshtein(chaine1, chaine2));
    }
}