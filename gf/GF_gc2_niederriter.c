#include<stdio.h>
#include<stdlib.h>
#include"GF.h"
#include"n_lds_GF.h"

static GF_GC_MATRIX *g_gm;       /* Gray code, generator matrix */
static unsigned long *g_ix;     /* Gray code, preceding vector */
static unsigned char is_init = 1;
static unsigned long count;

void GF_gc2_niederreiter(int dim, double *x, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s){

  int i,j,k,l;
  GF_MATRIX *g_m, stock_m;
  unsigned char a[]={1,3,7,15}, *ix;
  int line, digit, flag = 0;
  unsigned char base, baseDigits, matrixSize;

  // initialize
  base = getBase();
  baseDigits = getBaseDigits();
  matrixSize = getMatrixSize();
  ix = GF_newVector();
  stock_m = GF_newMatrix();
  
  // at the first time
  if( is_init ){
    unsigned char *c, *g;
    c = (unsigned char*)malloc(sizeof(unsigned char)*matrixSize);
    g = (unsigned char*)malloc(sizeof(unsigned char)*matrixSize);

    // g is gray code of jump
    count = jump;
    for(j=0;j<matrixSize;j++)
      c[j] = GF_getBits(base, count >> baseDigits*j);
    for(i=0;i<matrixSize-1;i++)
      g[i] = GF_getBits(base, c[i] - c[i+1] + base);
    g[matrixSize-1] = c[matrixSize-1];

    // get generating matrix
    g_m = (GF_MATRIX*)malloc(sizeof(GF_MATRIX)*dim);
    GF_matrix_gen( dim, g_m, seed, flag_g, flag_l, flag_s );

    // compress generating matrix and i-th vector to small size matrix and small size vector, unsigned long.
    g_gm = (GF_GC_MATRIX*)malloc(sizeof(GF_GC_MATRIX)*dim);
    g_ix = (unsigned long*)calloc(dim,sizeof(unsigned long));
    for(i=0;i<dim;i++){

      // compress to vector.
      GF_multMatrixVector(g_m[i],g,ix);
      for(j=0;j<matrixSize;j++)
	g_ix[i] = (g_ix[i] << baseDigits) + ix[j];

      // compress to matrix.
      g_gm[i] = GF_gc_newMatrix();
      for( j=0; j<baseDigits ; j++ ){
	GF_multMatrixScalar(g_m[i],a[j],stock_m);
	for( k=0; k<matrixSize; k++ ){
	  g_gm[i][j][k] = 0;
	  for( l=0; l<matrixSize; l++)
	    g_gm[i][j][k] = (g_gm[i][j][k] << baseDigits) + stock_m[l][k];
	}
      }
    }

    // close
    free(c);
    free(g);
    free(g_m);
    is_init = 0;
  }

  // line = (changed digit) - 1
  digit = count;
  line = 0;
  while( GF_getBits(base, digit) == base - 1 ){
    line++;
    digit >>=baseDigits;
  }

  // digit is a value at line.
  digit = GF_getBits(base, (GF_getBits(base, digit) - GF_getBits(base, digit >> baseDigits) + base));

  //
  while( (digit & 0x01) == 1 ){
    flag++;
    digit >>= 1;
  }
 
  // adjust flag when flag = base - 1.
  if(flag == baseDigits)
    flag = baseDigits - 1;
 
  //
  for( i = 0; i < dim; i++ ){
    g_ix[i] ^= g_gm[i][flag][line];
    x[i] = g_ix[i]/POWER_2_32;
  }

  // next
  count++;
}
