#include<stdio.h>
#include "GF.h"

static unsigned char base;

void GF_multMatrixMatrix(unsigned char base, unsigned char **a, unsigned char **b, unsigned char **r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF; i++)
        for (j=0; j<MAXDIGITS_GF; j++){
            unsigned long t;
            t = 0;
            for (k=0; k<MAXDIGITS_GF; k++)
                t = GF_add(t, GF_mult(a[i][k], b[k][j]));
            r[i][j] = t;
        }
}


void GF_multMatrixVec(GF_MATRIX a, GF_VECTOR x, GF_VECTOR r){
    int i, k;
    for (i=0; i<MAXDIGITS_GF; i++) {
        unsigned long t;
        t = 0;
        for (k=0; k<MAXDIGITS_GF; k++)
            t = GF_add(t, GF_mult(a[i][k], x[k]));
        r[i] = t;
    }
}

void GF_multMatrixScalar(GF_MATRIX a, unsigned char c, GF_MATRIX r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF; i++)
        for (j=0; j<MAXDIGITS_GF; j++)
	  r[i][j] = GF_mult(a[i][j],c);
}

void GF_displayMatrix(GF_MATRIX a){
  int i,j;

  for( i=0; i<MAXDIGITS_GF; i++ ){
    for( j=0; j<MAXDIGITS_GF; j++ )
      printf("%2d",a[i][j]);
    printf("\n");
  }
}
    
        
