#include<stdio.h>
#include<stdlib.h>
#include"GF4.h"
#include"n_lds_GF4.h"

static GF4_MATRIX *g_m;       /* generator matrix */
static char is_init = 1;
static unsigned long count;

void GF4_niederriter(int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s){

  int i,j;
  GF4_VECTOR r,s;
  double xx;
  unsigned long k;


  if( is_init ){
    g_m = (GF4_MATRIX*)calloc(dim,sizeof(GF4_MATRIX));
    GF4_matrix_gen(dim, g_m, seed, flug_g, flug_l, flug_s);
    count = jump;
    is_init = 0;
  }
  
  k = count;
  for( j=0; j < MAXDIGITS_GF4; j++){
    r[j] = (char)GF4_get_bits(k);
    k >>= BITS_GF4;
  }
  for( i=0; i < dim; i++){
    xx = 0;
    GF4_matrix_vec_mult(g_m[i], r, s);
    for( j=MAXDIGITS_GF4-1; j >= 0; j--)
      xx = (xx+s[j])/BASE_GF4;
    x[i] = xx;
  }
  count++;
}
