/*Auteur : MABROUK Fayez
 *Création : 03-02-2022
 *Modification: 09-02-2022*/

#include "TP2.h"


int main(){
    FILE *f;
    Arbre a;
        
    f = fopen("arbre1","rt");
    remplit_arbre(&a,f);
    printf("hauteur d'arbre : %d\n",hauteur(a));
    printf("nombre des noeuds : %d\n",nombre_noeuds(a));
    printf("nombre des feuilles : %d\n",nombre_feuilles(a));
    printf("nombre des noeuds internes : %d\n",nombre_noeuds_internes(a));
    printf("nombre des noeuds a deux fils : %d\n",deux_fils(a));
    if(binaire(a) == 0)
        printf("l'arbre n'est pas binaire\n");
    else 
        printf("l'arbre est binaire\n");
    
    /*construit_arbre_quelconque(f);*/
    /*Arbre a = alloue_noeud (1) ;*/
    /*a->fg = alloue_noeud (2) ;
    a->fg->fd = alloue_noeud (42) ;
    printf("binary %d ",binaire(a));
    construit_arbre_quelconque(in);*/
    /*fclose(f);*/
    return 0;
}