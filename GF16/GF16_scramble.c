#include"GF16.h"

void GF16_scramble(unsigned long seed, GF16_MATRIX a, GF16_MATRIX b){

  int i,j;
  GF16_MATRIX r;

  for (i=0; i<MAXDIGITS_GF16; i++) {
    for (j=0; j<=i; j++)
      r[i][j] = GF16_rand(seed);
    while (r[i][i]==0)
      r[i][i] = GF16_rand(seed);
    for (j=i+1; j<MAXDIGITS_GF16; j++)
	    r[i][j] = 0;
  }
  GF16_matrix_mult(r, a, b);

}
