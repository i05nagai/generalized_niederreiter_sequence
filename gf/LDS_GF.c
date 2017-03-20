#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"GF.h"
#include"n_lds_GF.h"

static int Dim = 1, SeqType = 0;
static int Flag_g = 0, Flag_l = 0, Flag_s = 0;
static int Jump, Seed;

static void (*lds)( int, double*, unsigned long, unsigned long, int, int, int );

void LDS_GF( double *x ){
  lds(Dim, x, Jump, Seed, Flag_g, Flag_l, Flag_s);
}


void LDS_initialize( unsigned char base, int dim, double *x, int seqType, unsigned long jump, unsigned long seed, int flag_g, int flag_l, int flag_s ) {

  if( dim <= 0  || dim > MAXDIM ){
    fprintf(stderr,"dimension must be between 1 and %d.\n",MAXDIM);
    exit(1);
  }
  if( seqType < 0 || seqType > 2 ){
    fprintf(stderr,"seqType  must be between 0 and 2.\n");
    exit(1);
  }
  if( flag_g !=0 && flag_g != 1 ){
    fprintf(stderr,"flag_g must be 0 or 1.\n");
    exit(1);
  }
  if( flag_l !=0 && flag_l != 1 ){
    fprintf(stderr,"flag_g must be 0 or 1.\n");
    exit(1);
  }
  if( flag_s !=0 && flag_s != 1 ){
    fprintf(stderr,"flag_g must be 0 or 1.\n");
    exit(1);
  }

  Dim = dim;
  SeqType = seqType;
  Jump = jump;
  Seed = seed;
  Flag_g = flag_g;
  Flag_l = flag_l;
  Flag_s = flag_s;
  
  GF_initialize( base );

  switch( SeqType ) {
  case 0:
    lds = GF_niederreiter; break;
  case 1:
    lds = GF_gc_niederreiter; break;
  case 2:
    lds = GF_gc2_niederreiter; break;
  default :
    break;
  }
}
