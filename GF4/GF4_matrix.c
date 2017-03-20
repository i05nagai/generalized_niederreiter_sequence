#include<stdio.h>
#include "GF4.h"

void GF4_matrix_mult(GF4_MATRIX a, GF4_MATRIX b, GF4_MATRIX r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF4; i++)
        for (j=0; j<MAXDIGITS_GF4; j++){
            unsigned long t;
            t = 0;
            for (k=0; k<MAXDIGITS_GF4; k++)
                t = GF4_add(t, GF4_mult(a[i][k], b[k][j]));
            r[i][j] = t;
        }
}


void GF4_matrix_vec_mult(GF4_MATRIX a, GF4_VECTOR x, GF4_VECTOR r){
    int i, k;
    for (i=0; i<MAXDIGITS_GF4; i++) {
        unsigned long t;
        t = 0;
        for (k=0; k<MAXDIGITS_GF4; k++)
            t = GF4_add(t, GF4_mult(a[i][k], x[k]));
        r[i] = t;
    }
}

void GF4_matrix_mult_scalar(GF4_MATRIX a, char c, GF4_MATRIX r){
    int i, j, k;
    for (i=0; i<MAXDIGITS_GF4; i++)
        for (j=0; j<MAXDIGITS_GF4; j++)
	  r[i][j] = GF4_mult(a[i][j],c);
}

void GF4_matrix_display(GF4_MATRIX a){
  int i,j;

  for( i=0; i<MAXDIGITS_GF4; i++ ){
    for( j=0; j<MAXDIGITS_GF4; j++ )
      printf("%2d",a[i][j]);
    printf("\n");
  }
}
    
        
