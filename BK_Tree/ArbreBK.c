/* Auteurs: MABROUK Fayez
            BASHEER AHAMED Nafis.
 *Création :08-04-2022
 *Modification : 22-04-2022*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArbreBK.h"
#include "Levenshtein.h"
#include "Listes.h"



ArbreBK alloue_noeud(char *mot,int val) {
    ArbreBK arbre;

    arbre = (ArbreBK)malloc(sizeof(NoeudBK));
    if (arbre == NULL)  {
        fprintf(stderr, "erreur d'allocation.\n");
        return NULL;
    }

    arbre->mot = (char *)malloc(sizeof(char) * strlen(mot));
    if (arbre->mot == NULL) {
        fprintf(stderr, "erreur d'allocation de la chaine.\n");
        free(arbre);
        return NULL;
    }

    strcpy (arbre->mot, mot);
    arbre->valeur = val;
    arbre->filsG = arbre->frereD  = NULL;
    return arbre;
}

int inserer_dans_ArbreBK(ArbreBK * A, char * mot) {
    ArbreBK * fils = NULL;
    int d; 

    if(*A== NULL) {
        *A = alloue_noeud(mot, 0);
        return 1;
    }

    d = Levenshtein((*A)->mot, mot);
    if(!d)
        return 0;
    fils = &((*A)->filsG);

    while (1) {
        while(*fils) {
            if((*fils)->valeur == d) {
                d = Levenshtein((*fils)->mot, mot);
                fils = &((*fils)->filsG);
                break;
            }
            else if ((*fils)->valeur > d) {
                ArbreBK noeudtmp;
                noeudtmp = alloue_noeud(mot, d);
                noeudtmp->frereD = *fils;
                *fils = noeudtmp;
                return 1;
            }
            else
                fils = &((*fils)->frereD);
        }
        if(!*fils) {
            *fils = alloue_noeud(mot, d);
            return 1;
        }
    }
}


int appartient_BK(ArbreBK A,char* mot) {
    ArbreBK  B ;
    ArbreBK fils;
    int d;

    if (A == NULL)
        return 0;
    B = A;

    while(1) {
        d = Levenshtein(B->mot, mot);
        if(!d) 
            return 1;
        fils = B->filsG;
        while(fils) {
            if(fils->valeur == d) {
                B = fils;
                break;
            }
            else 
            fils = fils->frereD;
        }
        if(!fils) 
            return 0;
    }
}       

void rechercher_dans_ArbreBK(ArbreBK A, char * mot, Liste* corrections, int *seuil) {
    int d;
    if(A == NULL)
        return;
    else {
        d = Levenshtein(A->mot, mot);

        if(d == *seuil) {
            if(inserer_en_tete(corrections, A->mot) == 0)
                fprintf(stderr, "erreur lors de l'insertion du mot dans la liste\n");
        }

        if(d < *seuil) {
            liberer_Liste(corrections);
            if(inserer_en_tete(corrections, A->mot) == 0)
                fprintf(stderr, "erreur lors de l'insertion du mot dans la liste\n");
            *seuil = d;
        }

        if(A->filsG != NULL) {
            A = A->filsG;
            while (A != NULL) {
                if(abs((A->valeur - d)) <= *seuil)
                    rechercher_dans_ArbreBK(A, mot, corrections, seuil);
                A = A->frereD;
            }
        }
    }   
}

ArbreBK cree_ArbreBK(FILE * dico) {
	ArbreBK A;
    A = NULL;
	char mot[100];

	while(fscanf(dico,"%s", mot) != EOF) {
		inserer_dans_ArbreBK(&A, mot);
        
    }

	if (fclose(dico) == EOF) {
        fprintf(stderr, "erreur dans le fermeture du dictionnaire\n");
    }
    return A;
}

void liberer_ArbreBK(ArbreBK * A) {
    if((*A)->filsG != NULL)
        liberer_ArbreBK(&(*A)->filsG);
    if((*A)->frereD != NULL)
        liberer_ArbreBK(&(*A)->frereD);
    free(*A);
    *A = NULL;
}


void ecrireDebut(FILE *f) {
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "\tnode [shape=record, height=.1 ]\n");
    fprintf(f, "\tedge [tailclip=false, arrowtail = dot, dir=both];\n\n");
}

void ecrireArbre(FILE *f, ArbreBK a) {
    if (a != NULL) {
            fprintf(f, "\tn%p [label=\" <gauche> |{ %s|<here> %d }| <droit>\"]\n", a, a->mot,a->valeur);
        if (a->filsG != NULL) {
            fprintf(f, "\tn%p:gauche:c -> n%p:valeur;\n", a, a->filsG);
            ecrireArbre(f, a->filsG);
        }
        if (a->frereD != NULL) {
            fprintf(f, "\tn%p:droit:c -> n%p:valeur;\n", a, a->frereD);
            ecrireArbre(f, a->frereD);
        }
    }
}

void ecrireFin(FILE *f) {
    fprintf(f, "}\n");
}

void dessine(FILE *f, ArbreBK a) {
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}

void creePDF(char *dot, char *pdf, ArbreBK a) {
    int len;
    FILE * out = fopen(dot, "w");
    dessine(out, a);
    fclose(out); 
    len = strlen(dot) + strlen(pdf) + 15;
    char cmd[len];
    strcpy(cmd, "dot -Tpdf ");
    strcat(cmd, dot);
    strcat(cmd, " -o ");
    strcat(cmd, pdf);
    system(cmd);
}

void afficher_ArbreBK(ArbreBK a) {
    creePDF("visualise.dot", "visualise.pdf", a);
    system("evince visualise.pdf &");
}




void affichage_proposition(ArbreBK dico, FILE* a_corriger, char *mot, Liste erreurs, Liste corrections) {
    int seuil;
    seuil = 100;

    while (fscanf(a_corriger, "%s", mot) == 1) {
        if (!(appartient_BK(dico, mot))) {
            if (inserer_en_tete(&erreurs, mot) == 0) {
            
                fprintf(stderr, "erreur d'insertion\n");
            }
            rechercher_dans_ArbreBK(dico, mot, &corrections, &seuil);
            affiche_saut(erreurs);
            afficher_corr(corrections, mot);
            liberer_Liste(&corrections);
            liberer_Liste(&erreurs);
            seuil = 100;
        }
    }
}
