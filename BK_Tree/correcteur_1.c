/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 30-03-2022
 *Modification : 02-04-2022*/

#include "ATR.h"
#include "Levenshtein.h"
#include "Listes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LETTRES 50

void verif_mot(char * c) {
    while (*c !=  '\0') {
        if (*c >= ' ' && *c <= '/') {
            *c = '\0';
        }
        if(*c == EOF) *c = '\0';
        if ('A' <= *c && *c <= 'Z')
            *c = *c - 'A' + 'a'; 
        c++;
    }
}




void parcours(ATR A, char buffer[], int indice, Liste *L, char * AE, int * d_min) {
    int d;

    if (A != NULL) {
       buffer[indice] = A->c;
        if (A->c == '\0') {
            d = Levenshtein(buffer,AE);
            if(d <= *d_min) {
                if(d < *d_min) {                   
                    *d_min = d;
                    liberer_Liste(L);
                }
                if (inserer_en_tete(L, buffer) == 0) 
                    fprintf(stderr, "erreur lors de l'insertion du mot dans la liste\n");
            }
        }

        else if (A->fils != NULL) {
            parcours(A->fils, buffer, indice + 1, L, AE, d_min);
        }
        if (A->gauche != NULL) 
            parcours(A->gauche, buffer, indice, L, AE, d_min);
        if(A->droit != NULL) {
            parcours(A->droit, buffer, indice, L, AE, d_min );
        }
    }
}

int main(int argc,char * argv[]) {
    Liste erreurs = NULL;
    Liste corrections = NULL;
    ATR dico;
    FILE * dico_f;
    char mot[100];
    FILE * a_corriger;
    char buffer[MAX_LETTRES];
    int indice;

    indice = 0;
    int d_min = 100;

    dico = creer_ATR_vide();
    dico_f = fopen(argv[2], "r");
    while(fscanf(dico_f, "%s", mot) == 1) {
        inserer_dans_ATR(&dico, mot);
    }  
    if (fclose(dico_f) == EOF) {
        fprintf(stderr, "erreur dans le fermeture du dictionnaire\n");
    }
    
    a_corriger = fopen(argv[1], "r");
    if (a_corriger == NULL) {
        fprintf(stderr, "Pas de fichier texte en argument\n");
        exit(EXIT_FAILURE);
    }
    
    while (fscanf(a_corriger, "%s", mot) == 1) {   
        verif_mot(mot);
        if (!(appartient(dico, mot))) {
            if (inserer_en_tete(&erreurs, mot) == 0) {
                fprintf(stderr, "erreur d'insertion\n");
            }
            parcours(dico, buffer, indice, &corrections, mot, &d_min);        
            affiche_saut(erreurs);
            afficher_corr(corrections, mot);
            liberer_Liste(&corrections);
            liberer_Liste(&erreurs);
            d_min = 100;
        }
    }

    if (fclose(a_corriger) == EOF) {
        fprintf(stderr, "erreur dans le fermeture du dictionnaire\n");
    }
    return 0;
}



