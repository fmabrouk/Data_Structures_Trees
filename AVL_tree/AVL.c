#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct noeud {
    int valeur;
    int bal;
    struct noeud *fg;
    struct noeud *fd;
} NoeudAVL, *AVL;


void ecrireDebut(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "node [ shape = record , height = .1 ]\n");
    fprintf(f, "edge [ tailclip = false , arrowtail = dot , dir = both ];\n\n");
}

void ecrireArbre(FILE *f, AVL a){
    
        if ( a!= NULL){
            fprintf(f, "\tn%p [ label =\"<gauche > | {%d |<here>  %d} | <droit >\"];\n",a, a->valeur,a->bal);
            if (a->fg != NULL){
                fprintf(f, "\tn%p: gauche : c -> n%p: valeur ;\n", a, a->fg);
                ecrireArbre(f, a->fg);
            }
            if (a->fd != NULL){
                fprintf(f, "\tn%p: droit : c -> n%p: valeur ;\n", a, a->fd);
                ecrireArbre(f, a->fd);    
            }
        }
    
}

void ecrireFin(FILE *f){
    fprintf(f, "}");
}

void dessine(FILE *f, AVL a){
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}

void creePDF (char * dot , char * pdf , AVL a) {

    int len;
    FILE * out = fopen (dot , "w") ;

    dessine (out , a) ;

    fclose (out) ;

    len = strlen ( dot ) + strlen ( pdf ) + 15;
    char cmd [ len ];

    strcpy (cmd , "dot  -Tpdf  ") ;
    strcat (cmd , dot ) ;
    strcat (cmd , " -o ") ;
    strcat (cmd , pdf) ;
    system (cmd) ;
}


int max(int a , int b){
    if(a>b) return a;
    else return b;
}
 

 
int maxbal(AVL *avl){
    if(*avl){
        return 1 + max(maxbal(&(*avl)->fg), maxbal(&(*avl)->fd));
    }
    else return 0;
}
 
void refreshbal(NoeudAVL **avl){
    if(*avl){
        (*avl)->bal = maxbal(&(*avl)->fg) - maxbal(&(*avl)->fd);
       
    }
}

void Rotation_G(NoeudAVL **avl){
    NoeudAVL *aux=(*avl)->fd;
     
    if(*avl){
        (*avl)->fd = aux->fg;
        aux->fg = (*avl);
        *avl = aux;
        refreshbal(&(*avl));
        refreshbal(&(*avl)->fg);
    }
}


/*
void Rotation_G (AVL *r){
    assert(*r);
    AVL d; 
    int i, j;
    
    d = (*r)->fd; (*r)->fd = d->fg; d->fg = *r;
   
    i = (*r)->bal; j = d->bal;
    if (j >= 0)
    (*r)->bal = i - j - 1;
    else
    (*r)->bal = i - 1;
    if ((*r)->bal <= 0)
    d->bal = j + (*r)->bal - 1;
    else
    d->bal = j - 1;
    
    *r = d;
}
*/


void Rotation_D(NoeudAVL **avl){
    NoeudAVL *aux=(*avl)->fg;
     
    if(*avl){
        (*avl)->fg = aux->fd;
        aux->fd = (*avl);
        *avl = aux;
        refreshbal(&(*avl));
        refreshbal(&(*avl)->fd);
    }
}



/*
void Rotation_D(AVL *r) {
    assert(*r);
   AVL d; 
    int i, j;
   
    d = (*r)->fg; (*r)->fg = d->fd; d->fd = *r;
    
    i = (*r)->bal; j = d->bal;
    if (j >= 0)
    (*r)->bal = i - j - 1;
    else
    (*r)->bal = i - 1;
    if ((*r)->bal <= 0)
    d->bal = j + (*r)->bal - 1;
    else
    d->bal = j - 1;
    *r = d;
}
*/


void Rotation_DG(AVL *r) {
    Rotation_D(&((*r)->fd));
    Rotation_G(r);
}

void Rotation_GD(AVL *r) {
    Rotation_G(&((*r)->fg));
    Rotation_D(r);
}


/*
void Equilibrer(AVL* A) {
    if ((*A)->bal == 2)
        if ((*A)->fd->bal >= 0)
             Rotation_G(A);
        else { 
            Rotation_DG(&((*A)->fd));
            Rotation_G(A);
    }
    else if ((*A)->bal == -2)
        if ((*A)->fg->bal <= 0)
            Rotation_D(A);
        else { 
            Rotation_G(&((*A)->fg));
            Rotation_D(A);
        }
}
*/
 


void Equilibrer (AVL *a){
    if ((*a)->bal == 2){
        if ((*a)->fd->bal >= 0)
            Rotation_G(a);
        else
            Rotation_DG(a);
    }
    if ((*a)->bal == -2){
        if ((*a)->fg->bal <= 0){
            Rotation_D(a);
        }
        else
            Rotation_GD(a);
    }
}




/*
void Equilibrer (AVL *a){
    if ((*a)->bal == 2){
        if ((*a)->fg->bal == -2)
            Rotation_GD(a);
        else
            Rotation_D(a);
    }
    if ((*a)->bal == -2){
        if ((*a)->fd->bal == 2)
            Rotation_DG(a);
        else
            Rotation_G(a);
    }
    else refreshbal(a);
}
*/

AVL alloue_noeud(int val) {

    AVL a = malloc(sizeof(NoeudAVL));
    if(a == NULL){
        fprintf(stderr,"Erreur allocation mémoire\n");
        return;
    }
    a->valeur = val;
    a->bal = 0;
    a->fd = NULL;
    a->fg = NULL;
    return a;
}

int Inserer(AVL *a, int i){
    int var;
    if (*a == NULL) {
        *a = alloue_noeud(i);
        return 1;
    } else if (i <= (*a)->valeur)
        var = -Inserer(&(*a)->fg,i);
    else
        var = Inserer(&(*a)->fd,i);
    if (var == 0)
        return 0;
    else {
        (*a)->bal = (*a)->bal + var;
        Equilibrer(a);
        if ((*a)->bal == 0) 
            return 0;
        else 
            return 1;
    }
}


int main(int argc,char * argv[]) {

    AVL a ;
    FILE * out;
    a = NULL;

    
    Inserer(&a,7);
    Inserer(&a,12);
    Inserer(&a,25);
    Inserer(&a,16);
    Inserer(&a,21);
    Inserer(&a,13);
    Inserer(&a,2);
    Inserer(&a,5);
    Inserer(&a,4);
    Inserer(&a,9);
    Inserer(&a,30);
    Inserer(&a,27);
    Inserer(&a,6);
    Inserer(&a,11);    
    out = fopen("visualise.dot", "w");
    if (out == NULL)
        printf("Erreur à l'ouverture du fichier\n");
    else {
        dessine(out, a);
    }
    fclose(out);
    system("dot -Tpdf visualise.dot -o visualise.pdf");
    system("evince visualise.pdf &");
    
    
    return 0;
}