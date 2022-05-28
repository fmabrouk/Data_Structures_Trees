/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 19-03-2022*/

#include "Listes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Cellule * allouer_Cellule(char * mot) {
    Cellule *res;
    
    res = (Cellule *)malloc(sizeof(Cellule));
    if ( res == NULL) {
        fprintf(stderr,"erreur d'allocation de la cellule.\n");
        return NULL;
    }
    res->mot = (char *) malloc(strlen(mot) * sizeof(char));
    if ( res->mot == NULL) {
        fprintf(stderr,"erreur d'allocation de la chaine.\n");
        return NULL;
    }
    strcpy (res->mot, mot);
    
    res->suivant = NULL;
    return res;
}

int inserer_en_tete(Liste * L, char * mot) {
    
    Liste *nouv_liste;
    if (*L == NULL) {
        *L = allouer_Cellule(mot);
        if (*L == NULL) return 0;
        (*L)->suivant = NULL;
        return 1;
    }
    if (((*nouv_liste) = allouer_Cellule(mot)) == NULL) 
        return 0;
    
    (*nouv_liste)->suivant = (*L); 
    *L = *nouv_liste;
    return 1;
}

Liste supp_tete_liste (Liste * liste){
    if ( (*liste) == NULL)
        return NULL;
    Liste tmp;
    tmp = *liste;
    *liste = (*liste)->suivant;
    return tmp; 
} 


void liberer_Liste(Liste * L) {
    if ((*L) == NULL)
        return;
    
    liberer_Liste(&(*L)->suivant);
    supp_tete_liste(&(*L));
}

void afficher_Liste(Liste L) {
    if( L == NULL) {
        fprintf(stderr, "Rien à afficher, la liste est vide.\n");
        return;
    }
    if (L->suivant != NULL) afficher_Liste(L->suivant);    
    printf("%s\n", L->mot);
}    

void affiche_saut(Liste L) {
    printf("mots mal orthographié(s) :\n");
    afficher_Liste(L);
}