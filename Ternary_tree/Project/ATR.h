/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 19-03-2022*/

#ifndef __ATR__H
#define __ATR__H

/*Structure pour l'arbre ternaire de recherche */
typedef struct noeud {
    char c ; 
    struct noeud * gauche ; 
    struct noeud * fils ; 
    struct noeud * droit;
} Noeud , *ATR ;

/*
    BUT : fonction responsable de créer un arbre ternaire de recherche vide.
    RETURN : renvoie un arbre ternaire de recherche.
*/
ATR creer_ATR_vide();

/*
    BUT : fonction responsable de libérer la mémoire.
    PARAM : un pointeur vers ATR .
*/
void liberer_ATR(ATR * A);

/*
    BUT : fonction responsable d'allouer la place en mémoire pour ATR.
    PARAM : c de type char.
    RETURN : renvoie un arbre de type ATR.
*/
ATR  alloue_noeud(char c);

/*
    BUT : fonction responsable d'ajouter une branche pour mot dans ATR.
    PARAM : A de type ATR * et mot de type char *.
*/
void ajoute_branche(ATR *A, char *mot);

/*
    BUT : fonction responsable d'insérer le mot dans ATR.
    PARAM : A de type ATR * et mot de type char*.
    RETURN : renvoie 0 en cas d'échec et 1 sinon.
*/
int inserer_dans_ATR(ATR * A, char * mot);

/*
    BUT : fonction responsable de vérifier si le mot est dans dico.
    PARAM : dico de type ATR et mot de type char*.
    RETURN : renvoie 0 en cas d'échec et 1 sinon.
*/
int appartient(ATR dico,char* mot);

/*
    BUT : fonction responsable de supprimer mot dans ATR.
    PARAM : A de type ATR* et mot de type char*.
*/
void supprimer_dans_ATR(ATR * A, char * mot);

/*
    BUT : fonction d'affichage auxiliaire .
    PARAM : A de type ATR. 
*/
void affiche_ATR_aux(ATR A, char buffer[], int indice);

/*
    BUT : fonction responsable d'afficher ATR .
    PARAM : A de type ATR. 
*/
void afficher_ATR(ATR A);


#endif