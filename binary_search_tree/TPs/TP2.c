/*Auteur : MABROUK Fayez
 *Création : 03-02-2022
 *Modification: 09-02-2022*/

#include "TP2.h"
/*..................Exercice1..............*/
Arbre alloue_noeud(int val)
{
    Arbre a = malloc(sizeof(Arbre));
    if(a == NULL){
        fprintf(stderr,"Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    a->valeur = val;
    a->fd = NULL;
    a->fg = NULL;

    printf("Création de %d..\n",a->valeur);

    return a;
}

/*..................exercice 2..................*/
int max(int a,int b)
{
  int maxi=(a > b) ?  a:  b;
  return maxi;
}

int hauteur(Arbre a)
{
    int hg,hd; 
    if(a == NULL)
        return -1;
  
    hg = hauteur(a->fg);
    
    hd = hauteur(a->fd);
    return 1 + max(hg,hd);
}
int nombre_noeuds(Arbre a)
{
    if(a == NULL)
		return 0;
    return (nombre_noeuds(a->fg) + nombre_noeuds(a->fd) + 1);
}
int nombre_noeuds_internes( Arbre a)
{
    if (a == NULL)
        return 0;
    if(a->fg == NULL && a->fd == NULL)
        return 0;
    return 1 + nombre_noeuds_internes(a->fg)+nombre_noeuds_internes(a->fd);
}

int nombre_feuilles(Arbre a)
{
    if(a== NULL)
        return 0;
    if(a->fg == NULL && a->fd == NULL)
        return 1; 
    return nombre_feuilles(a->fg)+nombre_feuilles(a->fd);
}
int deux_fils(Arbre a)
{
    int a_deux_fils  ;
    if(a== NULL)
        return 0;
    a_deux_fils = 0;
    if(a->fd  && a->fg)
        a_deux_fils = 1;
    return deux_fils(a->fd)+deux_fils(a->fg)+a_deux_fils;
}

/*..................exercice3....................*/
int remplit_arbre (Arbre *a, FILE *in) {
    int n;
    *a = NULL;
    fscanf(in, "%d", &n);
    if( n != 0){
        *a = alloue_noeud(n);
        remplit_arbre (&((*a)-> fg), in);
        remplit_arbre (& ((*a) -> fd), in);
    }
    return n;
}
int binaire(Arbre a)
{
    if(a == NULL )
        return 0;
    else if(a->fg == NULL && a->fd == NULL || a->fd  && a->fg)
        return 1;
    else  {
        binaire (a->fd);
        binaire(a->fg);
    }   
}
/*...................exercice4...................*/
Arbre construit_arbre_quelconque(FILE *in)
{   
    int val;
    fscanf(in,"%d",&val);
    if(val != 0){
        Arbre a = alloue_noeud(val);
        a->valeur = val;
        a->fg = construit_arbre_quelconque(in);
        a->fd = construit_arbre_quelconque(in);
    }
    return NULL;
}
void ecrit_arbre_quelconque(Arbre a, FILE *out)
{
    if(a == NULL)
        return;
    else
        fprintf(out,"%d\n",a->valeur);
    if(a->fd != NULL)
        ecrit_arbre_quelconque(a->fd,out);
    if(a->fg != NULL)
        ecrit_arbre_quelconque(a->fg,out);
}


