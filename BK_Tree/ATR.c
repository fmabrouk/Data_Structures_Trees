/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 16-03-2022*/
#include "ATR.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LETTRES 50


ATR creer_ATR_vide() {
    ATR arbre = (Noeud*)malloc(sizeof(Noeud));
    if (arbre == NULL)  {
        fprintf(stderr,"erreur d'allocation.\n");
        return NULL;
    }
    arbre->c = ' ';
    arbre->gauche = arbre->fils = arbre->droit = NULL;
    return arbre;
}


void liberer_ATR(ATR * A) {
    if ((*A)->gauche != NULL)
        liberer_ATR(&(*A)->gauche);
    if ((*A)->fils != NULL)
        liberer_ATR(&(*A)->fils);
    if ((*A)->droit != NULL)
        liberer_ATR(&(*A)->droit);
    free(*A);
    *A = NULL;
}


ATR  alloue_noeud(char c) {
    ATR arbre = (ATR) malloc(sizeof(Noeud));
    if (arbre != NULL) {
        if ('A' <= c && c <= 'Z')
            arbre->c = c - 'A' + 'a'; 
        else
            arbre->c = c;
        arbre->fils = arbre->droit = arbre->gauche = NULL;
    }
    return arbre;
}

    
void ajoute_branche(ATR *A, char *mot){
    if ((*A = alloue_noeud(*mot)) != NULL){
        if (*mot != '\0')
            ajoute_branche(&((*A)->fils),mot + 1);
    }
}


int inserer_dans_ATR(ATR * A, char * mot) {
    if (*A == NULL) {
        ajoute_branche(A, mot);
    }
    else {
        if ((*A)->c < *mot) {
            return inserer_dans_ATR(&((*A)->droit), mot);
        }
        else if ((*A)->c > *mot) {
            return inserer_dans_ATR(&((*A)->gauche), mot);
        }
        else if ((*A)->c == *mot && *mot != '\0') {
            return inserer_dans_ATR(&((*A)->fils), mot + 1);
        } 
    }
}



int appartient(ATR A,char* mot) {
    if (A == NULL)
        return 0;
    if (*mot < A->c)
        return appartient(A->gauche,mot);
    if (*mot == A->c) {
        if (*mot == '\0') {
            return 1;
        }
        return appartient(A->fils,mot + 1);
    }
    return appartient(A->droit,mot);
}       


void supprimer_dans_ATR(ATR * A, char * mot) {
    if (*A == NULL) return;

    if ((*A)->gauche == NULL && (*A)->droit == NULL && (*A)->fils == NULL) {
        free(*A);
        *A = NULL;
    }
    
    else if (*mot < (*A)->c) {
        supprimer_dans_ATR(&(*A)->gauche, mot);
    }

    else if (*mot > (*A)->c) {
        supprimer_dans_ATR(&(*A)->droit, mot);
    }

    else if ((*A)->c == *mot && *mot != '\0') {
            supprimer_dans_ATR(&((*A)->fils), mot + 1);
        }
}


void affiche_ATR_aux(ATR A, char buffer[], int indice) {
    if (A != NULL) {
       buffer[indice] = A->c;
        if (A->c == '\0') {
            printf("arbre affiche :%s\n", buffer);
        }
        else 
            affiche_ATR_aux(A->fils, buffer, indice + 1);
        
        if (A->gauche != NULL) 
            affiche_ATR_aux(A->gauche, buffer, indice);
        if(A->droit != NULL) {
            affiche_ATR_aux(A->droit, buffer, indice);
        }
    }

}


void afficher_ATR(ATR A) {
    char buffer[MAX_LETTRES];
    int indice;
    indice = 0;
    affiche_ATR_aux(A, buffer, indice);
}
