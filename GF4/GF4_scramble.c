#include"GF4.h"

void GF4_scramble(unsigned long seed, GF4_MATRIX a, GF4_MATRIX b){

  int i,j;
  GF4_MATRIX r;

  for (i=0; i<MAXDIGITS_GF4; i++) {
    for (j=0; j<=i; j++)
      r[i][j] = GF4_rand(seed);
    while (r[i][i]==0)
      r[i][i] = GF4_rand(seed);
    for (j=i+1; j<MAXDIGITS_GF4; j++)
	    r[i][j] = 0;
  }
  GF4_matrix_mult(r, a, b);

}
