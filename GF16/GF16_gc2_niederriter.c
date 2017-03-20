#include<stdio.h>
#include<stdlib.h>
#include"GF16.h"
#include"n_lds_GF16.h"

static GF16_GC_MATRIX *g_gm;       /* Gray code, generator matrix */
static unsigned long *g_ix;     /* Gray code, preceding vector */
static char is_init = 1;
static unsigned long count;

void GF16_gc2_niederriter(int dim, double *x, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s){

  int i,j,k,l;
  GF16_MATRIX *g_m, stock_m;
  char a[]={1,3,7,15}, ix[MAXDIGITS_GF16];
  int line, digit, flug = 0;
  
  if( is_init ){
    char c[MAXDIGITS_GF16],g[MAXDIGITS_GF16];

    count = jump;
    for(j=0;j<MAXDIGITS_GF16;j++)
      c[j] = GF16_get_bits(count >> BITS_GF16*j);
    for(i=0;i<MAXDIGITS_GF16-1;i++)
      g[i] = GF16_get_bits( c[i] - c[i+1] + BASE_GF16);
    g[MAXDIGITS_GF16-1] = c[MAXDIGITS_GF16-1];

    g_m = (GF16_MATRIX*)calloc(dim,sizeof(GF16_MATRIX));
    GF16_matrix_gen( dim, g_m, seed, flug_g, flug_l, flug_s );

    g_gm = (GF16_GC_MATRIX*)calloc(dim,sizeof(GF16_GC_MATRIX));
    g_ix = (unsigned long*)calloc(dim,sizeof(unsigned long));
    for(i=0;i<dim;i++){
      GF16_matrix_vec_mult(g_m[i],g,ix);
      for(j=0;j<MAXDIGITS_GF16;j++)
	g_ix[i] = (g_ix[i] << BITS_GF16) + ix[j];
      for( j=0; j<BITS_GF16 ; j++ ){
	GF16_matrix_mult_scalar(g_m[i],a[j],stock_m);
	for( k=0; k<MAXDIGITS_GF16; k++ )
	  for( l=0; l<MAXDIGITS_GF16; l++)
	    g_gm[i][j][k] = (g_gm[i][j][k] << BITS_GF16) + stock_m[l][k];
      }
    }
    free(g_m);
    is_init = 0;
  }
  
  digit = count;
  line = 0;
  while( GF16_get_bits(digit) == BASE_GF16 - 1 ){
    line++;
    digit >>=BITS_GF16;
  }
  digit = GF16_get_bits((GF16_get_bits(digit) - GF16_get_bits(digit >> BITS_GF16) + BASE_GF16));
  while( (digit & 0x01) == 1 ){
    flug++;
    digit >>= 1;
  }
  if(flug == BITS_GF16)
    flug = BITS_GF16 - 1;
  for( i = 0; i < dim; i++ ){
    g_ix[i] ^= g_gm[i][flug][line];
    x[i] = g_ix[i]/POWER_2_32;
  }
  count++;
}
