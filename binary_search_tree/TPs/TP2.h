/*Auteur : MABROUK Fayez
 *Création : 03-02-2022
 *Modification: 09-02-2022*/

#ifndef __TP2__H
#define __TP2__H

#include <stdlib.h>
#include <stdio.h>
typedef struct noeud {
 int valeur ; /* étiquette du nœud */
 struct noeud * fg ; /* adresse du fils gauche */
 struct noeud * fd ; /* adresse du fils droit */
} Noeud , * Arbre ;

Arbre alloue_noeud(int val);
int max(int a,int b);
int hauteur(Arbre a);
int  nombre_noeuds(Arbre a);
int nombre_noeuds_internes( Arbre a);
int nombre_feuilles(Arbre a);
int deux_fils(Arbre a);
int binaire(Arbre a);
Arbre construit_arbre_quelconque(FILE *in);
void ecrit_arbre_quelconque(Arbre a,FILE *out);

#endif