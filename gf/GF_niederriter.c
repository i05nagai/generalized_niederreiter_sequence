#include<stdio.h>
#include<stdlib.h>
#include"GF.h"
#include"n_lds_GF.h"

static GF_MATRIX *g_m;       /* generator matrix */
static unsigned char is_init = 1;
static unsigned long count;

void GF_niederreiter(int dim, double *x, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s){

  int i,j;
  GF_VECTOR r,s;
  double xx;
  unsigned long k;
  unsigned char base, baseDigits, matrixSize;

  base = getBase();
  baseDigits = getBaseDigits();
  matrixSize = getMatrixSize();

  r = GF_newVector();
  s = GF_newVector();

  if( is_init ){
    g_m = (GF_MATRIX *)malloc(sizeof(GF_MATRIX)*dim);
    GF_matrix_gen(dim, g_m, seed, flag_g, flag_l, flag_s);
    count = jump;
    is_init = 0;
  }
  
  k = count;
  for( j=0; j<matrixSize; j++){
    r[j] = (unsigned char)GF_getBits(base, k);
    k >>= baseDigits;
  }
  for( i=0; i<dim; i++){
    xx = 0;
    GF_multMatrixVector(g_m[i], r, s);
    for( j=matrixSize-1; j>=0; j--)
      xx = (xx+s[j])/base;
    x[i] = xx;
  }
  count++;
}
