#include <stdio.h>
#include <stdlib.h>
#include "GF4.h"
#include "n_lds_GF4.h"

void LDS_Gauss_GF4( int dim, double *x, int seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s ) {
  int i;
  int gt_dim;
  double *y,Gauss_y[2];

  gt_dim = (dim+1)/2*2;
  y = (double*)malloc(gt_dim*sizeof(double));
  LDS_GF4( gt_dim, y, seq_type, jump, seed, flug_g, flug_l, flug_s);
  for(i=0;i<gt_dim-2;i+=2){
    GaussDevBM(y[i],y[i+1],Gauss_y);
    x[i] = Gauss_y[0];
    x[i+1] = Gauss_y[1];
  }
  GaussDevBM(y[gt_dim-2],y[gt_dim-1],Gauss_y);
  x[gt_dim-2] = Gauss_y[0];
  if(dim==gt_dim)
    x[gt_dim-1] = Gauss_y[1];
  free(y);
}
