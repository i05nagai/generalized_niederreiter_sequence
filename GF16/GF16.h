#ifndef _GF16_H_
#define _GF16_H_

extern char GF16_mult_table[];
extern char GF16_inv_table[];

/*** define ***/
#define BASE_GF16 16
#define BITS_GF16 4
#define POWER_2_32 4294967296.0
#define MAXDIGITS_GF16 (32/BITS_GF16)
#define MAXDIM 20000

#define GF16_add( a, b ) ((a)^(b))
#define GF16_sub( a, b ) ((a)^(b))
#define GF16_mult( a, b ) GF16_mult_table[BASE_GF16*(a)+(b)]
#define GF16_inv( a ) GF16_inv_table[a]
#define GF16_get_bits( a ) ((a) & (BASE_GF16 - 1))

typedef char GF16_MATRIX[MAXDIGITS_GF16][MAXDIGITS_GF16];
typedef char GF16_VECTOR[MAXDIGITS_GF16];
typedef unsigned long GF16_GC_MATRIX[BITS_GF16][MAXDIGITS_GF16];

struct _GF16X{
	unsigned int degree;
	char *a;
};

typedef struct _GF16X GF16X;

/*** in GF16.c ***/
char GF16_power( char a, char b );

char GF16_rand( unsigned long seed );
void GF16_rand_initialize( void );

/*** in GF16_matrix.c ***/
void GF16_matrix_mult( GF16_MATRIX a, GF16_MATRIX b, GF16_MATRIX r );
void GF16_matrix_vec_mult( GF16_MATRIX a, GF16_VECTOR x, GF16_VECTOR r );
void GF16_matrix_mult_scalar( GF16_MATRIX a, char c, GF16_MATRIX r );
void GF16_matrix_display( GF16_MATRIX a );

/*
* GF16[X]: polynomial over GF(16)
*/

/*** in GF16X.c ***/
GF16X *GF16X_new( int degree );
void GF16X_del( GF16X *t );
void GF16X_mult_GF16( char a, GF16X *t );
void GF16X_copy( GF16X *from, GF16X *to );
int GF16X_is_zero( GF16X *t );
void GF16X_set_zero( GF16X *t );
void GF16X_clear( GF16X *t );
void GF16X_mult_x_n( GF16X *a, int n );
void GF16X_add_assign( GF16X *a, GF16X *b );
void GF16X_sub_assign( GF16X *a, GF16X *b );
void GF16X_div( GF16X *a, GF16X *b, GF16X *q, GF16X *r );
void GF16X_display( GF16X *X );

/*** in GF16_scramble.c ***/
void GF16_scramble( unsigned long seed, GF16_MATRIX a, GF16_MATRIX b);

#endif
