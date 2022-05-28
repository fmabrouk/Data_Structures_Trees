/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 02-04-2022*/

#ifndef __CELLULE__H
#define __CELLULE__H



/*Structure pour la cellule*/
typedef struct cellule {
    char * mot;
    struct cellule * suivant;
} Cellule, *Liste;

/*
    BUT : fonction responsable d'allouer la place dans la mémoire .
    PARAM : tableau de chaine
    RETURN : pointeur vers cellule.
*/
Cellule * allouer_Cellule(char * mot);

/*
    BUT : fonction responsable d'ajouter un mot au debut de liste.
    PARAM : L de type cellule ** et mot de type char *.
    RETURN :renvoie 0 en cas d'échec sinon elle renvoie 1.
*/
int inserer_en_tete(Liste * L, char * mot);

/*
    BUT: fonction responsable de supprimer un mot de la tete de liste.
    PARAM : liste de type Liste *.
    RETURN : renvoie 0 en cas d'échec sinon elle renvoie 1.
*/
Liste supp_tete_liste (Liste * liste);

/*
    BUT : fonction responsable de libérer la mémoire.
    PARAM : liste * de type cellule **.
*/
void liberer_Liste(Liste * L);

/*
    BUT : fonction responsable d'afficher la liste.
    PARAM : L de type Liste.
*/
void afficher_Liste(Liste L);

/*
    BUT : fonction qui appelle afficher_liste et
           précède l'affichage de "mots mal orthographié(s) :".
    PARAM : L de type Liste.
*/
void affiche_saut(Liste L);

/*
    BUT : fonction responsable d'afficher la liste de corrections 
            et mettre virgule apres chaque propostion obtenu.
    PARAM : L de type Liste et mot de type char *.
*/
void afficher_corr(Liste L, char *mot);

/*
    BUT : fonction qui appelle afficher_corr et
           précède l'affichage de "Propostion(s) :".
    PARAM : L de type Liste.
*/
void afficher_Liste_corr(Liste L);

#endif 