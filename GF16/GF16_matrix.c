#include<stdio.h>
#include "GF16.h"

void GF16_matrix_mult(GF16_MATRIX a, GF16_MATRIX b, GF16_MATRIX r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF16; i++)
        for (j=0; j<MAXDIGITS_GF16; j++){
            unsigned long t;
            t = 0;
            for (k=0; k<MAXDIGITS_GF16; k++)
                t = GF16_add(t, GF16_mult(a[i][k], b[k][j]));
            r[i][j] = t;
        }
}


void GF16_matrix_vec_mult(GF16_MATRIX a, GF16_VECTOR x, GF16_VECTOR r){
    int i, k;
    for (i=0; i<MAXDIGITS_GF16; i++) {
        unsigned long t;
        t = 0;
        for (k=0; k<MAXDIGITS_GF16; k++)
            t = GF16_add(t, GF16_mult(a[i][k], x[k]));
        r[i] = t;
    }
}

void GF16_matrix_mult_scalar(GF16_MATRIX a, char c, GF16_MATRIX r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF16; i++)
        for (j=0; j<MAXDIGITS_GF16; j++)
	  r[i][j] = GF16_mult(a[i][j],c);
}

void GF16_matrix_display(GF16_MATRIX a){
  int i,j;

  for( i=0; i<MAXDIGITS_GF16; i++ ){
    for( j=0; j<MAXDIGITS_GF16; j++ )
      printf("%3d",a[i][j]);
    printf("\n");
  }
}
    
        
