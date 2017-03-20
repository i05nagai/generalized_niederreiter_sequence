#include<stdio.h>
#include<stdlib.h>
#include"GF.h"
#include"n_lds_GF.h"

static GF_MATRIX *g_m;       /* generator matrix */
static GF_VECTOR *ix;     /* preceding vector */
static unsigned char is_init = 1;
static unsigned long count;

void GF_gc_niederreiter( int dim, double *x, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s ){
  int i,j;
  int line, digit, flag = 0;
  double xx;
  unsigned char a[] = {1,3,7,15};
  unsigned char base, baseDigits, matrixSize;

  // initialize
  base = getBase();
  baseDigits = getBaseDigits();
  matrixSize = getMatrixSize();

  if( is_init ){
    unsigned char c[matrixSize],g[matrixSize];

    count = jump;
    for(j=0;j<matrixSize;j++)
      c[j] = (unsigned char)GF_getBits(base, count >> baseDigits*j ) ;
    for(i=0;i<getMatrixSize()-1;i++)
      g[i] = (unsigned char)GF_getBits(base, c[i] - c[i+1] + base );
    g[matrixSize-1] = c[matrixSize-1];

    g_m = (GF_MATRIX*)malloc(sizeof(GF_MATRIX)*dim);
    GF_matrix_gen( dim, g_m, seed, flag_g, flag_l, flag_s );
    ix = (GF_VECTOR*)malloc(sizeof(GF_VECTOR)*dim );

    for( i = 0; i < dim; i++ ){
      ix[i] = GF_newVector();
      GF_multMatrixVector(g_m[i], g, ix[i]);
    }
    is_init = 0;
  }

  // line = (changed digit) - 1.
  digit = count;
  line = 0;
  while( GF_getBits(base, digit) == base - 1 ){
    line++;
    digit >>= baseDigits;
  }

  // digit is a value at digit line.
  digit = GF_getBits(base, GF_getBits(base, digit) - GF_getBits(base, digit >> baseDigits) + base);

  // flag is baseDigits of digit.
  while( (digit & 0x01) == 1 ){
    flag++;
    digit >>= 1;
  }

  // adjust flag when flag = base - 1.
  if(flag == baseDigits)
    flag = baseDigits - 1;

  //
  for( i = 0; i < dim; i++ ){
    for( j = 0; j < matrixSize; j++ )
      ix[i][j] = GF_add(ix[i][j], GF_mult(a[flag], g_m[i][j][line]));
    xx = 0;
    for( j = matrixSize-1; j >= 0; j--)
      xx = (xx+ix[i][j])/base;
    x[i] = xx;
  }

  // next
  count++;

}
