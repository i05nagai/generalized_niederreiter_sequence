#include<stdio.h>
#include<stdlib.h>
#include"GF.h"
#include<gsl/gsl_rng.h>

// GF4 and GF16 tables
//static unsigned char GF4_multTable[] = {0,0,0,0,0,1,2,3,0,2,3,1,0,3,1,2};
//static unsigned char GF4_invTable[] = {0,1,3,2};

//static unsigned char GF16_multTable[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,2,4,6,8,10,12,14,15,13,11,9,7,5,3,1,0,3,6,5,12,15,10,9,7,4,1,2,11,8,13,14,0,4,8,12,15,11,7,3,1,5,9,13,14,10,6,2,0,5,10,15,11,14,1,4,9,12,3,6,2,7,8,13,0,6,12,10,7,1,11,13,14,8,2,4,9,15,5,3,0,7,14,9,3,4,13,10,6,1,8,15,5,2,11,12,0,8,15,7,1,9,14,6,2,10,13,5,3,11,12,4,0,9,13,4,5,12,8,1,10,3,7,14,15,6,2,11,0,10,11,1,9,3,2,8,13,7,6,12,4,14,15,5,0,11,9,2,13,6,4,15,5,14,12,7,8,3,1,10,0,12,7,11,14,2,9,5,3,15,4,8,13,1,10,6,0,13,5,8,10,7,15,2,11,6,14,3,1,12,4,9,0,14,3,13,6,8,5,11,12,2,15,1,10,4,9,7,0,15,1,14,2,13,3,12,4,11,5,10,6,9,7,8};
static unsigned char multTable[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,2,4,6,8,10,12,14,15,13,11,9,7,5,3,1,0,3,6,5,12,15,10,9,7,4,1,2,11,8,13,14,0,4,8,12,15,11,7,3,1,5,9,13,14,10,6,2,0,5,10,15,11,14,1,4,9,12,3,6,2,7,8,13,0,6,12,10,7,1,11,13,14,8,2,4,9,15,5,3,0,7,14,9,3,4,13,10,6,1,8,15,5,2,11,12,0,8,15,7,1,9,14,6,2,10,13,5,3,11,12,4,0,9,13,4,5,12,8,1,10,3,7,14,15,6,2,11,0,10,11,1,9,3,2,8,13,7,6,12,4,14,15,5,0,11,9,2,13,6,4,15,5,14,12,7,8,3,1,10,0,12,7,11,14,2,9,5,3,15,4,8,13,1,10,6,0,13,5,8,10,7,15,2,11,6,14,3,1,12,4,9,0,14,3,13,6,8,5,11,12,2,15,1,10,4,9,7,0,15,1,14,2,13,3,12,4,11,5,10,6,9,7,8};
//static unsigned char GF16_invTable[] = {0,1,15,10,8,6,5,9,4,7,3,14,13,12,11,2};
static unsigned char invTable[] = {0,1,15,10,8,6,5,9,4,7,3,14,13,12,11,2};

//static unsigned char *multTable, *invTable;

// common variables
static unsigned char base;
static unsigned char baseDigits;
static unsigned char matrixSize;

// initialize
void GF_initialize(unsigned char inputBase){

  if( inputBase == 4 ){
    //    multTable = GF4_multTable;
    //    invTable = GF4_invTable;
    base = 4;
    baseDigits = 2;
    matrixSize= 32/baseDigits;
  }

  if( inputBase == 16 ){
    //    multTable = GF16_multTable;
    //    invTable = GF16_invTable;
    base = 16;
    baseDigits = 4;
    matrixSize= 32/baseDigits;
  }
  
  if( base != 4 && base != 16 ){
    fprintf(stderr, "base should be 4 or 16.\n");
    exit(1);
  }

}

// getter
unsigned char getBase(void){
  return base;
}

unsigned char getBaseDigits(void){
  return baseDigits;
}

unsigned char getMatrixSize(void){
  return matrixSize;
}

// arithmetic operations on GF4 or GF16
unsigned char GF_mult(unsigned char a, unsigned char b){
  return multTable[base*a+b];
}

unsigned char GF_inv(unsigned char a){
  return invTable[(int)a];
}

unsigned char GF_power(unsigned char a, unsigned char b){

  unsigned char y,z;

  z = 1;
  y = a;
  while ( b >= 1 ){
    if ( b & 1 )
      z = GF_mult(y, z);
    b >>= 1;
    y = GF_mult(y, y);
  }

  return z;

}

static int GF_randInit = 1;
static gsl_rng *mt19937;
unsigned char GF_rand(unsigned long seed){

  if( GF_randInit ){
    /** int_genrand(seed); **/
    mt19937 = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(mt19937, seed);
    GF_randInit = 0;
  }

  /** v = tp*genrand_real2(); **/
  return base * gsl_rng_uniform(mt19937);

}

void GF_randInitialize(void){
  GF_randInit = 1;
}

// arithmetic operations for matrix
GF_MATRIX GF_newMatrix( void ){
  int i;
  GF_MATRIX matrix;

  matrix = (GF_MATRIX)malloc(sizeof(unsigned char *)*matrixSize);
  for( i=0; i<matrixSize; i++ )
    matrix[i] = (unsigned char *)malloc(sizeof(unsigned char)*matrixSize);
  return matrix;
}

void GF_freeMatrix( GF_MATRIX matrix ){
  int i;
  
  for( i=0; i<matrixSize; i++ )
    free( matrix[i] );
  free(matrix);
}

void GF_multMatrixMatrix(GF_MATRIX a, GF_MATRIX b, GF_MATRIX r){
  int i, j, k;
  unsigned long t;
  
  for( i=0; i<matrixSize; i++ )
    for( j=0; j<matrixSize; j++ ){
      t = 0;
      for( k=0; k<matrixSize; k++ )
	t = GF_add(t, GF_mult(a[i][k], b[k][j]));
      r[i][j] = t;
    }
}

void GF_multMatrixVector(GF_MATRIX a, GF_VECTOR x, GF_VECTOR r){
  int i, k;
  unsigned long t;
  
  for( i=0; i<matrixSize; i++ ){
    t = 0;
    for( k=0; k<matrixSize; k++ )
      t = GF_add(t, GF_mult(a[i][k], x[k]));
    r[i] = t;
  }
}

void GF_multMatrixScalar(GF_MATRIX a, unsigned char c, GF_MATRIX r){
  int i, j;

  for( i=0; i<matrixSize; i++ )
    for( j=0; j<matrixSize; j++ )
      r[i][j] = GF_mult(a[i][j], c);
}

void GF_scramble(unsigned long seed, GF_MATRIX a, GF_MATRIX b){
  
  int i,j;
  GF_MATRIX r;
  
  r = GF_newMatrix();
  for( i=0; i<matrixSize; i++ ){
    for( j=0; j<=i; j++ )
      r[i][j] = GF_rand(seed);
    while( r[i][i] == 0 )
      r[i][i] = GF_rand(seed);
    for( j=i+1; j<matrixSize; j++ )
      r[i][j] = 0;
  }
  GF_multMatrixMatrix(r, a, b);
  
}

void GF_displayMatrix(GF_MATRIX a){
  int i,j;

  if( base == 4 ){
    for( i=0; i<matrixSize; i++ ){
      for( j=0; j<matrixSize; j++ )
	printf("%2d", a[i][j]);
      printf("\n");
    }
  }

  if( base == 16 ){
    for( i=0; i<matrixSize; i++ ){
      for( j=0; j<matrixSize; j++ )
	printf("%3d", a[i][j]);
      printf("\n");
    }
  }
}

// create vector
GF_VECTOR GF_newVector( void ){
  GF_VECTOR vector;

  vector = (GF_VECTOR)calloc(matrixSize, sizeof(unsigned char));

  return vector;
}

void GF_freeVector( GF_VECTOR vector ){
  free(vector);
}

// create matrix for gray code
GF_GC_MATRIX GF_gc_newMatrix( void ){
  int i;
  GF_GC_MATRIX gc_matrix;

  gc_matrix = (GF_GC_MATRIX)malloc(sizeof(unsigned long *)*baseDigits);
  for( i=0; i<baseDigits; i++ )
    gc_matrix[i] = (unsigned long *)malloc(sizeof(unsigned long)*matrixSize);
  return gc_matrix;
}

void GF_gc_freeMatrix( GF_GC_MATRIX gc_matrix ){
  int i;
 
  for( i=0; i<baseDigits; i++ )
    free( gc_matrix[i] );
  free(gc_matrix);
}

void GF_gc_displayMatrix( GF_GC_MATRIX gc_matrix ){
  int i,j;

  for( i=0; i<baseDigits; i++ ){
    for( j=0; j<matrixSize; j++ )
      printf("%lx\n", gc_matrix[i][j]);
    printf("\n");
  }
}
