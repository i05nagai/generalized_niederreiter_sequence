#include<stdio.h>
#include<stdlib.h>
#include"GF16.h"
#include"n_lds_GF16.h"

static GF16_MATRIX *g_m;       /* generator matrix */
static GF16_VECTOR *ix;     /* preceding vector */
static char is_init = 1;
static unsigned long count;

void GF16_gc_niederriter( int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s ){
  int i,j,k,l;
  int line, digit, flug = 0;
  double xx;
  char a[] = {1,3,7,15};
  
  if( is_init ){
    char c[MAXDIGITS_GF16],g[MAXDIGITS_GF16];

    count = jump;
    for(j=0;j<MAXDIGITS_GF16;j++)
      c[j] = GF16_get_bits( count >> BITS_GF16*j ) ;
    for(i=0;i<MAXDIGITS_GF16-1;i++)
      g[i] = GF16_get_bits( c[i] - c[i+1] + BASE_GF16);
    g[MAXDIGITS_GF16-1] = c[MAXDIGITS_GF16-1];

    g_m = (GF16_MATRIX*)calloc(dim,sizeof(GF16_MATRIX));
    GF16_matrix_gen( dim, g_m, seed, flug_g, flug_l, flug_s );
    ix = (GF16_VECTOR*)calloc(dim, sizeof(GF16_VECTOR));
    for( i = 0; i < dim; i++ )
      GF16_matrix_vec_mult(g_m[i], g, ix[i]);
    is_init = 0;
  }

  digit = count;
  line = 0;
  while( GF16_get_bits(digit) == BASE_GF16 - 1 ){
    line++;
    digit >>= BITS_GF16;
  }
  digit = GF16_get_bits((GF16_get_bits(digit) - GF16_get_bits(digit >> BITS_GF16) + BASE_GF16));
  while( (digit & 0x01) == 1 ){
    flug++;
    digit >>= 1;
  }
 if(flug == BITS_GF16)
    flug = BITS_GF16 - 1;
 for( i = 0; i < dim; i++ ){
    for( j = 0; j < MAXDIGITS_GF16; j++ )
      ix[i][j] = GF16_add(ix[i][j], GF16_mult(a[flug], g_m[i][j][line]));
    xx = 0;
    for( j = MAXDIGITS_GF16-1; j >= 0; j--)
      xx = (xx+ix[i][j])/BASE_GF16;
    x[i] = xx;
  }
  count++;
}
