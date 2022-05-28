#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct neu{
    int val;
    struct neu *fg,*fd;
}Noeud,*Arbre;

typedef struct cel {
	struct _noeud *noeu;
	struct cel *suivant;
}Cellule, *Liste;
 
typedef struct file {
	struct cel *input;
	struct cel *output;
}File;

void ecrireDebut(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "node [ shape = record , height = .1 ]\n");
    fprintf(f, "edge [ tailclip = false , arrowtail = dot , dir = both ];\n\n");
}

void ecrireArbre(FILE *f, Arbre a){
    
        if ( a!= NULL){
            fprintf(f, "\tn%p [ label =\"<gauche > | <valeur> %d | <droit >\"];\n",a,a->val);
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

void dessine(FILE *f, Arbre a){
    ecrireDebut(f);
    ecrireArbre(f, a);
    ecrireFin(f);
}

void creePDF (char * dot , char * pdf , Arbre a) {

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

Arbre alloue_noeud(int val) {
    Arbre a =(Noeud*) malloc(sizeof(Noeud));
    if(a == NULL){
        fprintf(stderr,"Erreur allocation mémoire\n");
        return;
    }
    a->val = val;
    a->fd = NULL;
    a->fg = NULL;
    return a;
}
Arbre insere_noeud(Arbre * a, int n) {
    if( (*a) == NULL) {
        *a = alloue_noeud(n);
    }
    else {
        /*if (n == (*a)->val)
            return *a;*/
        if(n < (*a)->val) {
            (*a)->fg = insere_noeud(&((*a)->fg),n);
        }
        else { 
            (*a)->fd = insere_noeud(&((*a)->fd),n); 
        }
        return *a;
    }
}

int max(int a,int b) {
    int maxi=(a>b) ? a:b;
    return maxi;
}

int nombreFilsUnique(Arbre a) {
    if(a == NULL)
        return 0;
    if(a->fd  == NULL && a->fg == NULL)
        return 0;
    int cmp = nombreFilsUnique(a->fd) + nombreFilsUnique(a->fg);
    if(a->fd == NULL && a->fg != NULL)
        cmp +=1;
    if(a->fd != NULL && a->fg == NULL)
        cmp += 1;
    return cmp;
}

int estPondere(Arbre a) {
    if(a == NULL) 
        return 1;
    if(a -> fd && a -> fg) {
        if(a -> val != (a -> fd -> val + a -> fg -> val)) 
            return 0;
    }
    if(!a->fg && a->fd){
        if(a->val != a->fd->val)
            return 0;
    }
    if(!a->fd && a->fg){
        if(a->val != a->fg->val)
            return 0;
    }
    return estPondere(a->fd) && estPondere(a->fg);
}

int max_3_param(int a, int b, int c) {
    if ((a > b) && (a > c))
        return a;
    if ((b > a) && (b > c))
        return b;
    if ((c > a) && (c > b))
        return c;
}

int pondereGauche(Arbre a) {
    int max1,max2,max3,max4;
    if(a == NULL)
        return 1;
    if(a->fd && a->fg) {
            max1 = max_3_param(a->val,a->fg->val,a->fd->val);
            a->val = max1;
            max2 = max(a->fg->val,a->fd->val);
            a->fg->val = max2;
            a->fd->val = a->val - a->fg->val;
    }
    if(a->fd && !a->fg) {
            max3 = max(a->fd->val,a->val);
            a->val = a->fd->val = max3;
    }
    if(a->fg && !a->fd) {
            max4 = max(a->fg->val,a->val);
            a->val = a->fg->val = max4;
    }
    return pondereGauche(a->fd) && pondereGauche(a->fg);
}
/*manque des conditions*/
int est_Tournoi(Arbre a) {
    if(a == NULL)
        return 1;
    if(a->fd && a->fg) {
        if(a->val > a->fd->val && a->val > a->fg->val)
            return 0;
    }
    if(a->fd && !a->fg) {
        if(a->val > a->fd->val)
            return 0;
    }
    if(a->fg && !a->fd) {
        if(a->val > a->fg->val)
            return 0;
    }
    return estTournoi(a->fg) && estTournoi(a->fd);
}

int hauteur(Arbre a) {
    if(a == NULL)
        return -1;
    /*if(a->fd == NULL && a->fg == NULL) 
        return 0;*//*feuille*/
    return 1 +max(hauteur(a->fd),hauteur(a->fg));
}

int est_feuille(Arbre a) {
    if(a->fd == NULL && a->fg == NULL)
        return 1;
    return 0;
}

void affiche_feuille(Arbre a) {
    if(a!= NULL && a->fg ==NULL && a->fd == NULL)
        printf("l'étiquette : %d\n", a->val);
    if(a->fg !=NULL)
        affiche_feuille(a->fg);
    if(a->fd != NULL)
        affiche_feuille(a->fd);
}

void parcours_prefixe(Arbre a){
    if(a == NULL)
        return;
    printf("l'étiquette : %d\n",a->val);
    parcours_prefixe(a->fg);
    parcours_prefixe(a->fd);
}

/*fonction pour afficher les noeuds a un hauteur donne*/
void affiche(Arbre a,int haut) {
    if(a == NULL)
        printf("Rien à afficher,l'arbre est vide\n");
    if(haut == hauteur(a))
        printf("l'étiquette : %d\n",a->val);
    else if(haut < hauteur(a)) {
        if(a->fg != NULL)
            affiche(a->fg,haut);
            
        if(a->fd != NULL)
            affiche(a->fd,haut);
    }
}



void afficheNiveau(Arbre a,int Niveau) {
    if(a == NULL)
        printf("Rien à afficher,l'arbre est vide\n");
    if(Niveau == 1)
        printf("l'étiquette : %d\n",a->val);
    else if(Niveau > 1) {
        if(a->fg != NULL)
            afficheNiveau(a->fg,Niveau-1);
        if(a->fd != NULL)
            afficheNiveau(a->fd,Niveau-1);
    }
}

int countNodes(Noeud* root) {
    if (root == NULL)
        return (0);
    return (1 + countNodes(root->fg)+ countNodes(root->fd));
}

bool isCompleteUtil(Noeud* root,int index,int number_nodes) {
    /* An empty tree is complete*/
    if (root == NULL)
        return (true);
 
    /*Si l'index est affecté au courant
     nœud est supérieur à
     nombre de nœuds dans l'arbre,
     alors l'arbre n'est pas complet*/
    if (index >= number_nodes)
        return (false);
 
    /* Recur for lfgand right subtrees*/
    return (isCompleteUtil(root->fg,2 * index + 1,number_nodes)
            && isCompleteUtil(root->fd,2 * index + 2,number_nodes));
}

bool isHeapUtil(Noeud* root) {
    /*  Base case : single
     node satisfies property*/
    if (root->fg == NULL && root->fd == NULL)
        return (true);
 
    /*  node will be in second last level*/
    if (root->fd == NULL) {
        /*  check heap property at Node
          No recursive call ,
          because no need to check last level*/
        return (root->val >= root->fg->val);
    }
    else {
        /* Check heap property at Node and
          Recursive check heap property
           at fg and fd subtree*/
        if (root->val >= root->fg->val
            && root->val >= root->fd->val)
            return ((isHeapUtil(root->fg))
                    && (isHeapUtil(root->fd)));
        else
            return (false);
    }
}


bool isTournamentUtil(Noeud* root) {
    if(root == NULL)
        return (true);
    if (root->fg == NULL && root->fd == NULL)
        return (true);
    if (root->fd == NULL) {
        return (root->val <= root->fg->val);
    }
    if(root->fg == NULL) {
        return (root->val <= root->fd->val);
    }
    else {
        if (root->val <= root->fg->val && root->val <= root->fd->val)
            return ((isTournamentUtil(root->fg)) && (isTournamentUtil(root->fd)));
        else
            return (false);
    }
}

int estTournoi(Noeud* root) {
    if (isTournamentUtil(root))
        return 1;
    return 0;
}

bool isHeap(Noeud* root) {
    /* These two are used in
    isCompleteUtil()*/
    int node_count = countNodes(root);
    int index = 0;
 
    if (isCompleteUtil(root, index, node_count)
        && isHeapUtil(root))
        return true;
    return false;
}

int recherche_MIN(Arbre a) {
    if(a == NULL)
        return 0;
    Arbre b = NULL;
    while(a != NULL) {
        b = a;
        a = a->fg;
    }
    return b->val;
}

int recherche_MAX(Arbre a) {
    if(a == NULL)
        return 0;
    Arbre b = NULL;
    while(a != NULL) {
        b = a;
        a = a->fd;
    }
    return b->val;
}

int helper(Arbre root, int range_min, int range_max) {
    if(root == NULL)
        return 1;
    
    if (root->val < range_min || root->val > range_max)
        return 0;
    if (helper(root->fg, range_min, root->val-1))
        if (helper(root->fd, root->val+1, range_max))
            return 1;
    return 0;
}

/*fonction verifiant si larbre est Binary saerch tree(BST)*/
int isBST(Arbre root) {
    if (helper(root,recherche_MIN(root),recherche_MAX(root)))
        return 1;
    return 0;
}

int remplit_arbre(Arbre *a,FILE *in) {
    *a = NULL;
    int n;
    if(fscanf(in,"%d",&n) != EOF && n != 0) {
        *a = alloue_noeud(n);
        remplit_arbre(&((*a)->fg),in);
        remplit_arbre(&((*a)->fd),in);
    }
    return n;
}


/*stocker les elements dans un tabelau */
void storeInorder(Arbre node, int inorder[], int* index_ptr) {
    if (node == NULL)
        return;
    storeInorder(node->fg, inorder, index_ptr);
    inorder[*index_ptr] = node->val;
    (*index_ptr)++;
    storeInorder(node->fd, inorder, index_ptr);
}


/* Following function is needed for library function qsort()*/
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
 

/* A helper function that copies contents of arr[] to Binary Tree.
This function basically does Inorder traversal of Binary Tree and
one by one copy arr[] elements to Binary Tree nodes */
void arrayToBST(int* arr, Arbre root, int* index_ptr) {
    if (root == NULL)
        return;
    arrayToBST(arr, root->fg, index_ptr);
    root->val = arr[*index_ptr];
    (*index_ptr)++;
    arrayToBST(arr, root->fd, index_ptr);
}


/*This function converts a given Binary Tree to BST*//*int etiquetteEnAbR*/
void binaryTreeToBST(Arbre root,int min) {
    if (root == NULL)
        return;
    int n = countNodes(root);
    int* arr;
    arr =(int*)malloc(sizeof(int)*n);
    if(arr == NULL)
        fprintf(stderr,"erreur d'allocation\n");
    int i = 0;
    storeInorder(root, arr, &i);
    for(i=0;i<n;i++) {
        if(arr[i] < min)
            arr[i] += min;
    }
    qsort(arr, n, sizeof(arr[0]), compare);
    for(i=0;i<n;i++) {
        if(arr[i] == arr[i+1])
            arr[i] +=min;
    }        
    qsort(arr, n, sizeof(arr[0]), compare);
    i = 0;
    arrayToBST(arr, root, &i);
    free(arr);
}

void Fait(Arbre A,int n){
    if(A == NULL)
        return;
    A->val = n;
}
 
int main(int ragc,char*argv[]) {

    Arbre a;
    FILE *out;
    FILE * fichier;
    a = NULL;

    fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        fprintf(stderr, "Pas de fichier texte en argument\n");
        exit(1);
    }
    remplit_arbre(&a,fichier);
    /*binaryTreeToBST(a,5);*/
    /*
    a = insere_noeud(&a,8);
    a = insere_noeud(&a,3);
    a = insere_noeud(&a,2);
    a = insere_noeud(&a,1);
    a = insere_noeud(&a,5);
    a = insere_noeud(&a,7);
    a = insere_noeud(&a,9);*/
    /*
    pondereGauche(a);*/
    Fait(a,5);
    out = fopen("visualise.dot", "w");
    if (out == NULL)
        printf("Erreur à l'ouverture du fichier\n");
    else {
        dessine(out, a);
    }
    fclose(out);
    system("dot -Tpdf visualise.dot -o visualise.pdf");
    system("evince visualise.pdf &");
    
    /*if(estTournoi(a))
        printf(" a est un arbre Tournoi\n");
    else 
        printf(" a  n'est pas un arbre Tournoi \n");*/
    
    /*if (isHeap(a)) {
         out = fopen("visualise.dot", "w");
        if (out == NULL)
            printf("Erreur à l'ouverture du fichier\n");
        else {
            dessine(out, a);
        }
        fclose(out);
        system("dot -Tpdf visualise.dot -o visualise.pdf");
        system("evince visualise.pdf &");
    }
    else
        printf("Arbre n'est pas pondere\n");*/
    /*
    if(est_Tournoi(a))
        printf(" a est un arbre Tournoi\n");
    else 
        printf(" a  n'est pas un arbre Tournoi \n");*/

    /*if(isBST(a))
        printf("a est un arbre binare de recherche\n");
    else 
        printf("a n'est pas  un arbre binaire de recherche\n");*/
    /*printf("nombreFilsUnique : %d\n",nombreFilsUnique(a));
    printf("hauteur de l'arbre : %d\n",hauteur(a));*/
    /*affiche(a,1);*/
    /*binaryTreeToBST(a,10);*/
    /*if(isBST(a))
        printf("a est un arbre binare de recherche\n");
    else 
        printf("a n'est pas  un arbre binaire de recherche\n");*/
    
   /* printf("la valeur min : %d\n",recherche_MIN(a));
    printf("la valeur max : %d\n",recherche_MAX(a));*/
    /*afficheNiveau(a,3);*/
    return 0;
}