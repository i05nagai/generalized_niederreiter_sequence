#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "GF16.h"
#include "n_lds_GF16.h"

static int is_init = 1;
static int Dim = 1, Seq_type = 0;
static int Flug_g = 0, Flug_l = 0, Flug_s = 0;

static void (*lds)( int, double*, unsigned long, unsigned long, int, int, int );

void LDS_GF16( int dim, double *x, int seq_type, unsigned long jump, unsigned long seed, int flug_g, int flug_l, int flug_s ) {
  int i;

  if ( dim != Dim || seq_type != Seq_type || flug_g != Flug_g || flug_l != Flug_l || flug_s != Flug_s){
    if( dim <= 0  || dim > MAXDIM ){
      fprintf(stderr,"dimension must be between 1 and %d.\n",MAXDIM);
      exit(1);
    }
    if( seq_type < 0 || seq_type > 2 ){
      fprintf(stderr,"seq_type  must be between 0 and 2.\n");
      exit(1);
    }
    if( flug_g !=0 && flug_g != 1 ){
      fprintf(stderr,"flug_g must be 0 or 1.\n");
      exit(1);
    }
    if( flug_l !=0 && flug_l != 1 ){
      fprintf(stderr,"flug_g must be 0 or 1.\n");
      exit(1);
    }
    if( flug_s !=0 && flug_s != 1 ){
      fprintf(stderr,"flug_g must be 0 or 1.\n");
      exit(1);
    }
    Dim = dim;
    Seq_type = seq_type;
    Flug_g = flug_g;
    Flug_l = flug_l;
    Flug_s = flug_s;
    is_init = 1;
  }
  if ( is_init ) {
    switch( Seq_type ) {
    case 0:
      lds = GF16_niederriter; break;
    case 1:
      lds = GF16_gc_niederriter; break;
    case 2:
      lds = GF16_gc2_niederriter; break;
    default :
      break;
    }
  }
  lds(Dim, x, jump, seed, Flug_g, Flug_l, Flug_s);
}
