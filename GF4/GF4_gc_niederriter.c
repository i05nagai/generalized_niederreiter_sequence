#include<stdio.h>
#include<stdlib.h>
#include"GF4.h"
#include"n_lds_GF4.h"

static GF4_MATRIX *g_m;       /* generator matrix */
static GF4_VECTOR *ix;     /* preceding vector */
static char is_init = 1;
static unsigned long count;

void GF4_gc_niederriter( int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s ){
  int i,j,k,l;
  int line, digit, flug = 0;
  double xx;
  char a[] = {1,3};
  
  if( is_init ){
    char c[MAXDIGITS_GF4],g[MAXDIGITS_GF4];

    count = jump;
    for(j=0;j<MAXDIGITS_GF4;j++)
      c[j] = GF4_get_bits( count >> BITS_GF4*j ) ;
    for(i=0;i<MAXDIGITS_GF4-1;i++)
      g[i] = GF4_get_bits( c[i] - c[i+1] + BASE_GF4);
    g[MAXDIGITS_GF4-1] = c[MAXDIGITS_GF4-1];

    g_m = (GF4_MATRIX*)calloc(dim,sizeof(GF4_MATRIX));
    GF4_matrix_gen( dim, g_m, seed, flug_g, flug_l, flug_s );
    ix = (GF4_VECTOR*)calloc(dim, sizeof(GF4_VECTOR));
    for( i = 0; i < dim; i++ )
      GF4_matrix_vec_mult(g_m[i], g, ix[i]);
    is_init = 0;
  }

  digit = count;
  line = 0;
  while( GF4_get_bits(digit) == BASE_GF4 - 1 ){
    line++;
    digit >>= BITS_GF4;
  }
  digit = GF4_get_bits((GF4_get_bits(digit) - GF4_get_bits(digit >> BITS_GF4) + BASE_GF4));
  while( (digit & 0x01) == 1 ){
    flug++;
    digit >>= 1;
  }
  if(flug == BITS_GF4)
    flug = BITS_GF4 - 1;
  for( i = 0; i < dim; i++ ){
    for( j = 0; j < MAXDIGITS_GF4; j++ )
      ix[i][j] = GF4_add(ix[i][j], GF4_mult(a[flug], g_m[i][j][line]));
    xx = 0;
    for( j = MAXDIGITS_GF4-1; j >= 0; j--)
      xx = (xx+ix[i][j])/BASE_GF4;
    x[i] = xx;
  }
  count++;
}
