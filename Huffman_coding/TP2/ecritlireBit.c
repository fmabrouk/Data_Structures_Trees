

#include <stdio.h>
 typedef struct {
FILE *fich;
unsigned char stock;
char nbBit;
}FileBit;

void fEcritCharbin(FileBit *f,unsigned char n){
  int i;
  unsigned int mask=1;
  for (i=7;i>=0;i--){
    mask=1<<i;
    fEcrireBit(f,(n&mask)!=0);
    
  }
  printf("\n");
}

int fBitopen(FileBit *f,const char *path, const char *mode){
  if((f->fich=fopen(path,mode))==NULL)
     return 0;
  f->stock=0; 
  f->nbBit=0;
  return 1;
}
void fBitinit(FileBit *f,FILE* fich){
  f->fich=fich;
  f->stock=0; 
  f->nbBit=0;
}

int fBitclose(FileBit *f){
 
  if( f->nbBit!=0){
 /* decaler a gauche les derniers bits si necessaire*/
    if  (f->nbBit!=8)
      f->stock<<=8-f->nbBit;
    fputc( f->stock,f->fich);
  }
  return fclose(f->fich);
}
int fLireBit(FileBit *f){
  int n;
if( f->nbBit==0){
  if ((n=fgetc(f->fich))==EOF)
    return EOF;
  f->stock=n;
  f->nbBit=8;
 }
 f->nbBit--;
 return (f->stock>>f->nbBit)&1;
}

int fEcrireBit(FileBit  *f, int bit){
  int coderetour =1;
if( f->nbBit==8){
    f->nbBit=0;
    coderetour=fputc(f->stock,f->fich);
  }
  f->nbBit++;
  f->stock=(f->stock<<1)|bit;
  return coderetour;

}


int main(int argc, char **argv){
  FileBit f;
  int i;
  fBitinit(&f,stdout);

    fEcritCharbin(&f,'a'); 
    fEcritCharbin(&f,'b');
    /*'d'*/
    fEcrireBit(&f,0);
    fEcrireBit(&f,1);
    fEcrireBit(&f,1);
    fEcrireBit(&f,0);
    fEcrireBit(&f,0);
    fEcrireBit(&f,1);
    fEcrireBit(&f, 0);
    fEcrireBit(&f,0) ;
    fEcrireBit(&f,0);/*pour vider le buffer*/

    printf("\n*******************\n");printf("entrez 3 char\n");
   fBitinit(&f,stdin);
    for(i=0;i<24;i++){
      printf( "%d",fLireBit(&f));
      if ((i+1)%8==0)
	printf("\n");
    }
  printf("\n");
  return 0;
}
