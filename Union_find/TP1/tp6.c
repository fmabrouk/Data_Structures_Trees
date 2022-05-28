#include<stdlib.h>
#include<stdio.h>
#include<time.h>


typedef struct unionfind {
 int taille ; /* Taille des tableaux */
 int * pere ; /* Tableau des peres */
 int * rang ; /* Tableau des rangs */
 unsigned nb_appels ;
} unionfind_t ;

unionfind_t* initialisation(int N){
    unionfind_t* tmp;
    int* tab_p;
    int* tab_r;
    int i;
    tmp = (unionfind_t*)malloc(sizeof(unionfind_t));
    if(tmp == NULL){
        printf("Error !");
        return 0;
    }
    tab_p = (int*)malloc(sizeof(int)*N);
    tab_r = (int*)malloc(sizeof(int)*N);
    if(tab_p == NULL||tab_r == NULL){
        printf("Error !");
        return 0;
    }
    for(i = 0; i < N; i++){
        tab_p[i] = i;
        tab_r[i] = 1;
    }
    tmp->pere = tab_p;
    tmp->rang = tab_r;
    tmp->taille = N;
    tmp->nb_appels = 0;
    return tmp;

}
int trouve_naif(unionfind_t* partition, int x){
    int i;
    for(i = x; i != partition->pere[i]; i=partition->pere[i] ){
        partition->nb_appels ++;
    }
    return partition->pere[i];
}

void fusion_naive(unionfind_t* partition, int x, int y){
    int p, q;
    p = trouve_naif(partition, x);
    q = trouve_naif(partition, y);
    if(p != q){
        partition->pere[q] = p;
    }
}

int trouve_compresse(unionfind_t* partition, int x){
    int elem;
    if(partition->pere[x] != x){
        elem = trouve_compresse(partition, partition->pere[x]);
    }
    return elem;
}

void fusion_rang(unionfind_t* partition, int x, int y){
    int x_rang, y_rang;
    int x_pere, y_pere;

    x_rang = partition->rang[x];
    y_rang = partition->rang[y];

    x_pere = trouve_compresse(partition, x);
    y_pere = trouve_compresse(partition, y);

    if(x_rang == y_rang){
        partition->pere[y_pere] = x_pere;
        partition->rang[x_pere] ++;
    }

    if(x_rang > y_rang){
        partition->pere[y_pere] = x_pere;        
    }

    if(y_rang > x_rang){
        partition->pere[x_pere] = y_pere;        
    }


}
int main() {
    unionfind_t* ensemble;
    ensemble = initialisation(4);
    srand(time(NULL));
    



    return 0;
}