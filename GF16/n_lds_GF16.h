#ifndef _N_LDS_GF16_H_
#define _N_LDS_GF16_H_

#include"GF16.h"

/*** each file ***/
void LDS_GF16( int dim, double *x, int Seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF16_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF16_gc_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF16_gc2_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF16_matrix_gen(int dim, GF16_MATRIX *g_m, unsigned long seed, int flug_g, int flug_l, int flug_s);

void LDS_Gauss_GF16(int dim, double *x, int Seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);

#endif
