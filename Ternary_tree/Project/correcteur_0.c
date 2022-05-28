/*Auteurs : MABROUK Fayez 
            BASHEER AHAMED Nafis
 *Création : 16-03-2022
 *Modification : 19-03-2022*/

/*to execute : ./correcteur_2 a_corriger_0.txt dico_1.dico */
#include "ATR.h"
#include "Listes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void verif_mot(char * c) {
    while (*c !=  '\0') {
        if (*c >= ' ' && *c <= '/') {
            *c = '\0';
        }
        
         if ('A' <= *c && *c <= 'Z')
            *c = *c - 'A' + 'a'; 
      
        
        c++;
        
    }
}



int main(int argc, char * argv[]) {

    Liste erreurs = NULL;
    
    ATR dico;
    FILE * dico_f;
    char mot[100];
    FILE * a_corriger;
    
    

    dico = creer_ATR_vide();
    dico_f = fopen(argv[2], "r");
    while(fscanf(dico_f, "%s", mot) == 1) {
        inserer_dans_ATR(&dico, mot);
    }  
    if (fclose(dico_f) == EOF) {
        fprintf(stderr, "erreur dans le fermeture du dictionnaire\n");
    }
    
  
      
    a_corriger = fopen(argv[1], "r");
    if (a_corriger == NULL) {
        fprintf(stderr, "Pas de fichier texte en argument\n");
        exit(EXIT_FAILURE);
    }
        
    while (fscanf(a_corriger, "%s", mot) == 1) {
        
       
        verif_mot(mot);
        if (!(appartient(dico, mot))) {
          
        
            if (inserer_en_tete(&erreurs, mot) == 0) {
            
                fprintf(stderr, "erreur d'insertion\n");
            }
        }
        
    }
     if (fclose(a_corriger) == EOF) {
        fprintf(stderr, "erreur dans le fermeture du dictionnaire\n");
    }
	
    
    

    affiche_saut(erreurs);
    return 0;
}
