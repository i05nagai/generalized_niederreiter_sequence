#include<stdio.h>
#include<stdlib.h>
#include"GF16.h"
#include"n_lds_GF16.h"

static GF16_MATRIX *g_m;       /* generator matrix */
static char is_init = 1;
static unsigned long count;

void GF16_niederriter(int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s){

  int i,j;
  GF16_VECTOR r,s;
  double xx;
  unsigned long k;


  if( is_init ){
    g_m = (GF16_MATRIX*)calloc(dim,sizeof(GF16_MATRIX));
    GF16_matrix_gen(dim, g_m, seed, flug_g, flug_l, flug_s);
    count = jump;
    is_init = 0;
  }
  
  k = count;
  for( j=0; j < MAXDIGITS_GF16; j++){
    r[j] = (char)GF16_get_bits(k);
    k >>= BITS_GF16;
  }
  for( i=0; i < dim; i++){
    xx = 0;
    GF16_matrix_vec_mult(g_m[i], r, s);
    for( j=MAXDIGITS_GF16-1; j >= 0; j--)
      xx = (xx+s[j])/BASE_GF16;
    x[i] = xx;
  }
  count++;
}
