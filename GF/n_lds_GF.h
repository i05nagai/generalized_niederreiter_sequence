#ifndef _N_LDS_GF_H_
#define _N_LDS_GF_H_

#include"GF.h"

/*** each file ***/
//void LDS_GF(int dim, double *x, unsigned char base, int Seq_type, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s);

void LDS_GF( double *x );
void LDS_initialize( unsigned char base, int dim, double *x, int seqType, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s );
void GF_niederreiter(int dim, double *ix, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s);
void GF_gc_niederreiter(int dim, double *ix, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s);
void GF_gc2_niederreiter(int dim, double *ix, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s);
void GF_matrix_gen(int dim, GF_MATRIX *g_m, unsigned long seed, int flag_g, int flag_l, int flag_s);

void LDS_Gauss_GF(int dim, double *x, unsigned char base, int Seq_type, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s);

#endif

