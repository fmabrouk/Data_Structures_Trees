/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 02-04-2022*/

#include "Listes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Cellule * allouer_Cellule(char * mot) {
    Cellule *res = (Cellule *)malloc(sizeof(Cellule));
    
    if (res == NULL) {
        fprintf(stderr, "erreur d'allocation de la cellule.\n");
        return NULL;
    }
    
    res->mot = (char *)malloc((strlen(mot) + 3) * sizeof(char));
    if (res->mot == NULL) {
        fprintf(stderr, "erreur d'allocation de la chaine.\n");
        return NULL;
    }
    strcpy(res->mot, mot);
    res->suivant = NULL;
    return res;
}

int inserer_en_tete(Liste * L, char * mot) {
    if (*L == NULL) {
        *L = allouer_Cellule(mot);
        if (*L == NULL) return 0;
        (*L)->suivant = NULL;
        return 1;
    }
   
    Liste *nouv_liste = NULL;
    nouv_liste = (Liste *)malloc(sizeof(Liste));
    if (nouv_liste == NULL) 
        fprintf(stderr, "*nouv_liste est NULL\n");
    
    *nouv_liste = allouer_Cellule(mot);
    
    if (*nouv_liste == NULL)  {
        free(nouv_liste);
        return 0;
    }
    (*nouv_liste)->suivant = *L; 
    *L = *nouv_liste;
    return 1;
}


Liste supp_tete_liste (Liste * liste){
    if (liste == NULL)
        return NULL;
    Liste tmp;
    tmp = *liste;
    *liste = (*liste)->suivant;
    return tmp; 
} 

void liberer_Liste(Liste * L) {
    if (*L == NULL)
        return;
    liberer_Liste(&((*L)->suivant));
    supp_tete_liste(L);
}

void afficher_Liste(Liste L) {
    if(L == NULL) {
        fprintf(stderr, "Rien à afficher, la liste est vide.\n");
        return;
    }
    if (L->suivant != NULL) 
        afficher_Liste(L->suivant);    
    printf("%s\n", L->mot);    
}    

void afficher_Liste_corr(Liste L) {
    if(L == NULL) {
        fprintf(stderr, "Rien à afficher, la liste est vide.\n");
        return;
    }
    while (L->suivant != NULL) {
        printf("%s, ",L->mot);
        L = L->suivant;
    }
    printf("%s\n", L->mot);
}    


void affiche_saut(Liste L) {
    printf("mots mal orthographié : ");
    afficher_Liste(L);
}

void afficher_corr(Liste L, char *mot) {
    printf("Proposition(s) : ");
    afficher_Liste_corr(L);
    
}