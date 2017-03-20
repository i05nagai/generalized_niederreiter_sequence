#ifndef _N_LDS_GF4_H_
#define _N_LDS_GF4_H_

#include"GF4.h"

/*** each file ***/
void LDS_GF4(int dim, double *x, int Seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF4_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF4_gc_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF4_gc2_niederriter(int dim, double *ix, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);
void GF4_matrix_gen(int dim, GF4_MATRIX *g_m, unsigned long seed, int flug_g, int flug_l, int flug_s);

void LDS_Gauss_GF4(int dim, double *x, int Seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s);

#endif
