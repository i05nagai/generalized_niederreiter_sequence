#ifndef _GF4_H_
#define _GF4_H_

extern char GF4_mult_table[];
extern char GF4_inv_table[];

/*** define ***/
#define BASE_GF4 4
#define BITS_GF4 2
#define POWER_2_32 4294967296.0
#define MAXDIGITS_GF4 (32/BITS_GF4)
#define MAXDIM 20000

#define GF4_add( a, b ) ((a)^(b))
#define GF4_sub( a, b ) ((a)^(b))
#define GF4_mult( a, b ) GF4_mult_table[BASE_GF4*(a)+(b)]
#define GF4_inv( a ) GF4_inv_table[a]
#define GF4_get_bits( a ) ((a) & (BASE_GF4 - 1))

typedef char GF4_MATRIX[MAXDIGITS_GF4][MAXDIGITS_GF4];
typedef char GF4_VECTOR[MAXDIGITS_GF4];
typedef unsigned long GF4_GC_MATRIX[BITS_GF4][MAXDIGITS_GF4];

struct _GF4X{
	unsigned int degree;
	char *a;
};

typedef struct _GF4X GF4X;

/*** in GF4.c ***/
char GF4_power( char a, char b );

char GF4_rand( unsigned long seed );
void GF4_rand_initialize( void );

/*** in GF4_matrix.c ***/
void GF4_matrix_mult( GF4_MATRIX a, GF4_MATRIX b, GF4_MATRIX r );
void GF4_matrix_vec_mult( GF4_MATRIX a, GF4_VECTOR x, GF4_VECTOR r );
void GF4_matrix_mult_scalar( GF4_MATRIX a, char c, GF4_MATRIX r );
void GF4_matrix_display( GF4_MATRIX a );

/*
* GF4[X]: polynomial over GF(4)
*/

/*** in GF4X.c ***/
GF4X *GF4X_new( int degree );
void GF4X_del( GF4X *t );
void GF4X_mult_GF4( char a, GF4X *t );
void GF4X_copy( GF4X *from, GF4X *to );
int GF4X_is_zero( GF4X *t );
void GF4X_set_zero( GF4X *t );
void GF4X_clear( GF4X *t );
void GF4X_mult_x_n( GF4X *a, int n );
void GF4X_add_assign( GF4X *a, GF4X *b );
void GF4X_sub_assign( GF4X *a, GF4X *b );
void GF4X_div( GF4X *a, GF4X *b, GF4X *q, GF4X *r );
void GF4X_display( GF4X *X );

/*** in GF4_scramble.c ***/
void GF4_scramble( unsigned long seed, GF4_MATRIX a, GF4_MATRIX b);

#endif
