#include <stdio.h>
#include <stdlib.h>
#include "GF.h"
#include "n_lds_GF.h"

void LDS_Gauss_GF( int dim, double *x, unsigned char base, int seq_type, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s ) {
  int i;
  int gt_dim;
  double *y,Gauss_y[2];

  gt_dim = (dim+1)/2*2;
  y = (double*)malloc(gt_dim*sizeof(double));
  //  LDS_GF( gt_dim, y, base, seq_type, jump, seed, flag_g, flag_l, flag_s);
  LDS_GF( y );
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
