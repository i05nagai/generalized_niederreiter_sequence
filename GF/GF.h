#ifndef _GF_H_
#define _GF_H_

// macro difinition
#define POWER_2_32 4294967296.0
#define MAXDIM 20000
#define GF_BASE 4
#define GF_BASE_DIGITS 2

#define GF_getBits(value) ((value) & (GF_BASE-1))

// initialaize
void GF_initialize(unsigned char base);

// arithmetic operation on GF
#define GF_add(a, b) ((a)^(b))
#define GF_sub(a, b) ((a)^(b))
unsigned char GF_mult(unsigned char a, unsigned char b);
unsigned char GF_inv(unsigned char a);
unsigned char GF_power(unsigned char a, unsigned char b);
unsigned char GF_rand( unsigned long seed );
void GF_randInitialize( void );

// structure
struct _GFX{
	unsigned int degree;
	unsigned char *a;
};

typedef struct _GFX GFX;


// type definition
typedef unsigned char** GF_MATRIX;
typedef unsigned char* GF_VECTOR;
typedef unsigned long** GF_GC_MATRIX;


// matrix
GF_MATRIX GF_newMatrix(void);
void GF_freeMatrix(GF_MATRIX m);
void GF_multMatrix( GF_MATRIX a, GF_MATRIX b, GF_MATRIX r );
void GF_multMatrixVector( GF_MATRIX a, GF_VECTOR b, GF_VECTOR r );
void GF_multMatrixScalar( GF_MATRIX a, unsigned char b, GF_MATRIX r );
void GF_scramble( unsigned long seed, unsigned char **a, unsigned char **b);
void GF_displayMatrix( GF_MATRIX a );

// vector
GF_VECTOR GF_newVector(void);
void GF_freeVector(GF_VECTOR v);

// gray code matrix
GF_GC_MATRIX GF_gc_newMatrix(void);
void GF_gc_freeMatrix(GF_GC_MATRIX gc_matrix);
void GF_gc_displayMatrix(GF_GC_MATRIX gc_matrix);

// arithmetic operation for polynomial on GF
GFX *GFX_new( int degree );
void GFX_del( GFX *t );
void GFX_multScalarGF( unsigned char a, GFX *t );
void GFX_copy( GFX *from, GFX *to );
int GFX_isZero( GFX *t );
void GFX_setZero( GFX *t );
void GFX_clear( GFX *t );
void GFX_mult_x_n( GFX *a, int n );
void GFX_add_assign( GFX *a, GFX *b );
void GFX_sub_assign( GFX *a, GFX *b );
void GFX_div( GFX *a, GFX *b, GFX *q, GFX *r );
void GFX_display( GFX *X );

void GaussDevBM(double x1, double x2, double y[]);
#endif

