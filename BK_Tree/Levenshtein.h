
/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 30-03-2022
 *Modification : 02-04-2022*/


#ifndef __LEVENSHTEIN__H
#define __LEVENSHTEIN__H

/*
    BUT : fonction permet de calculer le maximum de deux entiers.
    PARAM : a et b de type int.
    RETURN : renvoie le maximum.
*/
int MAX(int a, int b);

/*
    BUT : fonction permet de calculer le minimum de deux entiers.
    PARAM : a et b de type int.
    RETURN : renvoie le minimum.
*/
int MIN(int a, int b);

/*
    BUT : fonction permet de calculer le minimum de 3 entiers.
    PARAM : a , b et c de type int.
    RETURN : renvoie le minimum.
*/
int min_3_param(int a, int b, int c);

/*
    BUT : fonction permet de supprimer le premier carctère de chaine.
    PARAM : chaine de type char *.
    RETURN : renvoie le nouveau chaine apres suppression.
*/
char* chaine_supp_prem (char * chaine);

/*
    BUT : fonction responsable de calculer la distance de levenshtein entre les deux mots.
    PARAM : un et deux de type char*.
    RETURN : renvoie la distance de Levenshtein.
*/
int Levenshtein(char * un, char * deux);


#endif
