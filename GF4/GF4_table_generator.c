#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

#define N 4
#define BITS_GF4 2
#define IRRED_POLY 0x07

int main(void){
  int i,j,k,l;
  int a,b,c;
  int add[N][N],mult[N][N],inv[N][N];
  FILE *fp;
  
  fp = fopen("GF4_table","w");
  if(fp==NULL){
    fprintf(stderr,"can't open GF4_table.\n");
    exit(1);
  }
  
  /* addition */
  fprintf(fp,"addition\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      add[i][j] = i^j;
      fprintf(fp,"%3d",add[i][j]);
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"\n");
  
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      fprintf(fp,"%d,",add[i][j]);
  fprintf(fp,"\n\n");
  
  /* multiplycation */
  fprintf(fp,"multiplication\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      a = i;
      b = j;
      c = 0;
      for(k=0;k<N;k++){
	c ^= ( a & 0x01 ) * b;
	a >>= 1;
	b <<= 1;
      }
      for(l=32;l>BITS_GF4;l--){      
	l=0;
	while( (c >> l) != 0 )
	  l++;
	if(l>BITS_GF4)
	   c ^= IRRED_POLY << (l-BITS_GF4-1);
	else
	  break;
      }
      mult[i][j] = c;
      fprintf(fp,"%3d",mult[i][j]);
    }
    fprintf(fp,"\n");
  }
  fprintf(fp,"\n");
  
  for(i=0;i<N;i++)
    for(j=0;j<N;j++)
      fprintf(fp,"%d,",mult[i][j]);
  fprintf(fp,"\n\n");
  
  /* inverse */
  fprintf(fp,"inverse\n");
  for(i=1;i<N;i++)
    for(j=1;j<N;j++)
      if(mult[i][j] == 1)
	fprintf(fp,"%d,",j);
  
  fclose(fp);
}
