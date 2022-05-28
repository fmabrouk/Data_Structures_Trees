/* Auteurs: MABROUK Fayez
            BASHEER AHAMED Nafis.
 *Création :08-04-2022
 *Modification : 22-04-2022*/

/*to execute ./correcteur_2 a_corriger_1.txt dico_2.dico*/
#include <stdio.h>
#include <stdlib.h>
#include "ArbreBK.h"
#include "Listes.h"
#include "Levenshtein.h"


int main(int argc,char* argv[]) { 
    Liste corrections;
    Liste erreurs;
    ArbreBK dico;
    FILE * dico_f;
    char mot[100];
    int choix;
    FILE * a_corriger;

    erreurs = NULL;
    corrections = NULL;
    dico = NULL;
    dico_f = fopen(argv[2], "r");
    dico = cree_ArbreBK(dico_f);

    a_corriger = fopen(argv[1], "r");
    if (a_corriger == NULL) {
        fprintf(stderr, "Pas de fichier texte en argument\n");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        printf("1.AffichageBK\n2.Propositions\n3.Libérer_Arbre\n0.Quitter\n");
        scanf("%d", &choix);
        printf("choix :%d\n", choix);
        switch(choix) {
            case 1:
                afficher_ArbreBK(dico);
                break;
            case 2:
                affichage_proposition(dico, a_corriger, mot, erreurs, corrections);
                break;
            case 3:
                liberer_ArbreBK(&dico);
                printf("l'arbre est vide\n\n\n");
                break;
            case 0:
                exit(0);
                break;
            default:
                break;
        }
    }

    return 0;
}
