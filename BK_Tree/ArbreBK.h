/* Auteurs: MABROUK Fayez
            BASHEER AHAMED Nafis.
 *Création :08-04-2022
 *Modification : 22-04-2022*/

#ifndef __ARBREBK__H
#define __ARBREBK__H


#include "Listes.h"


/*structure pour ArbreBK */
typedef struct noeudBK {
    char * mot;
    int valeur;
    struct noeudBK * filsG;
    struct noeudBK * frereD;
} NoeudBK, * ArbreBK;


/*
    BUT : fonction permet d'allouer la place dans la mémoire pour mot
    et val.
    PARAM : mot de type mot* et val de type int.
    RETURN : renvoie un type ArbreBK.
*/
ArbreBK alloue_noeud(char * mot, int val);

/*
    BUT : fonction permet d'insérer le mot dans l'arbre.
    PARAM : A de type ArbreBK* et mot de type char*.
    RETURN : renvoie 1 si le mot est bien inséré et 0 sinon.
*/
int inserer_dans_ArbreBK(ArbreBK * A, char * mot);

/*
    BUT : fonction permet de vérifier si le mot est dans l'arbre.
    PARAM : A de type ArbreBK et mot de type char*.
    RETURN : renvoie A1 si le mot est déjà dans l'arbre et 0 sinon.
*/
int appartient_BK(ArbreBK A, char* mot);

/*
    BUT : fonction responsable de chercher les meilleurs propositions
    de mot en parcourant l'arbre.
    PARAM : A de type ArbreBK ,mot de type char*,corrections de type Liste*
    et seuil de type int*. 
*/
void rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste* corrections, int *seuil);


/*
    BUT : fonction responsable de créer l'arbreBK.
    PARAM : dico de type FILE*.
    RETURN : renvoie un type ArbreBK.
*/
ArbreBK cree_ArbreBK(FILE * dico);

/*
    BUT : fonction permet de libérer la place de l'arbre.
    PARAM : A de type ArbreBK*.
*/
void liberer_ArbreBK(ArbreBK * A);

/*
    BUT : fonction nécessaire pour l'affichage en utilisant langage dot.
    PARAM : f de type FILE*.
*/
void ecrireDebut(FILE *f);

/*
    BUT : fonction nécessaire pour l'affichage en utilisant langage dot.
    PARAM : f de type FILE* et a de type ArbreBK.
*/
void ecrireArbre(FILE *f, ArbreBK a);

/*
    BUT : fonction nécessaire pour l'affichage en utilisant langage dot.
    PARAM : f de type FILE*.
*/
void ecrireFin(FILE *f);

/*
    BUT : fonction nécessaire pour l'affichage en utilisant langage dot.
    PARAM : f de type FILE* et a de type ArbreBK.
*/
void dessine(FILE *f, ArbreBK a);

/*
    BUT : fonction nécessaire pour l'affichage en utilisant langage dot.
    PARAM : dot et pdf de type char* ,a de type ArbreBK.
*/
void creePDF(char *dot, char *pdf, ArbreBK a);

/*
    BUT : fonction permet d'afficher l'arbre en utilisant langage dot.
    PARAM : a de type ArbreBK.
*/
void afficher_ArbreBK(ArbreBK a);


/*
    BUT : fonction permet d'afficher les propositions de corrections
    pour chaque mot.
    PARAM : dico de type ArbreBK, a_corriger pointeur sur un fichier, mot qui
    est une chaine de caractère, erreurs et corrections qui sont des listes
*/
void affichage_proposition(ArbreBK dico, FILE* a_corriger, char *mot, Liste erreurs, Liste corrections); 

#endif


