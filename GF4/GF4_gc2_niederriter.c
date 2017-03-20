#include<stdio.h>
#include<stdlib.h>
#include"GF4.h"
#include"n_lds_GF4.h"

static GF4_GC_MATRIX *g_gm;       /* Gray code, generator matrix */
static unsigned long *g_ix;     /* Gray code, preceding vector */
static char is_init = 1;
static unsigned long count;

void GF4_gc2_niederriter(int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s){

  int i,j,k,l;
  GF4_MATRIX *g_m, stock_m;
  char a[]={1,3}, ix[MAXDIGITS_GF4];
  int line, digit, flug = 0;
  
  if( is_init ){
    char c[MAXDIGITS_GF4],g[MAXDIGITS_GF4];

    count = jump;
    for(j=0;j<MAXDIGITS_GF4;j++)
      c[j] = GF4_get_bits(count >> BITS_GF4*j);
    for(i=0;i<MAXDIGITS_GF4-1;i++)
      g[i] = GF4_get_bits( c[i] - c[i+1] + BASE_GF4);
    g[MAXDIGITS_GF4-1] = c[MAXDIGITS_GF4-1];

    g_m = (GF4_MATRIX*)calloc(dim,sizeof(GF4_MATRIX));
    GF4_matrix_gen( dim, g_m, seed, flug_g, flug_l, flug_s );

    g_gm = (GF4_GC_MATRIX*)calloc(dim,sizeof(GF4_GC_MATRIX));
    g_ix = (unsigned long*)calloc(dim,sizeof(unsigned long));
    for(i=0;i<dim;i++){
      GF4_matrix_vec_mult(g_m[i],g,ix);
      for(j=0;j<MAXDIGITS_GF4;j++)
	g_ix[i] = (g_ix[i] << BITS_GF4) + ix[j];
      for( j=0; j<BITS_GF4 ; j++ ){
	GF4_matrix_mult_scalar(g_m[i],a[j],stock_m);
	for( k=0; k<MAXDIGITS_GF4; k++ )
	  for( l=0; l<MAXDIGITS_GF4; l++)
	    g_gm[i][j][k] = (g_gm[i][j][k] << BITS_GF4) + stock_m[l][k];
      }
    }
    free(g_m);
    is_init = 0;
  }
  
  digit = count;
  line = 0;
  while( GF4_get_bits(digit) == BASE_GF4 - 1 ){
    line++;
    digit >>=BITS_GF4;
  }
  digit = GF4_get_bits((GF4_get_bits(digit) - GF4_get_bits(digit >> BITS_GF4) + BASE_GF4));
  while( (digit & 0x01) == 1 ){
    flug++;
    digit >>= 1;
  }
  if(flug == BITS_GF4)
    flug = BITS_GF4 - 1;
  for( i = 0; i < dim; i++ ){
    g_ix[i] ^= g_gm[i][flug][line];
    x[i] = g_ix[i]/POWER_2_32;
  }
  count++;
}
