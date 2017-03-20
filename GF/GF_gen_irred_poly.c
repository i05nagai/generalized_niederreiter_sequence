#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"GF.h"

int main ( int ac, char **av ){
  extern int optind;
  extern char *optarg;
  int c;
  
  char filename[5];
  int max, counter, i, deg;
  GFX **table, *poly, *q, *r;
  FILE *fp;
  
  // initial setting
  max = MAXDIM;
  deg = 1;
  
  // outer elements
  while((c = getopt(ac, av,"b:m:h"))!=EOF){
    switch(c){
    case 'm':
      max = atoi(optarg);
      if( max <= 0 ){
	fprintf(stderr,"Application Error: -m is allowed to be a natural number.\n!");
	exit(1);
      }
      break;
    case 'h':
      fprintf(stderr, "usage: GF_gen_irred_poly\n");
      fprintf(stderr, "\t-b <base number>\n");
      fprintf(stderr, "\t-m <max number>\n");
      fprintf(stderr, "\t-h <help>\n");
      exit(1);
      break;
    default:
      break;
    }
  }
  
  // open a output file.
  sprintf(filename, "IP%d", GF_BASE);
  fp = fopen(filename, "w");
  if( fp == NULL ){
    printf("can't open %s.\n", filename);
    exit(1);
  }
  
  // initialize
  GF_initialize( GF_BASE );
  
  // create irreducible polynomials
  poly = GFX_new( 0 );
  r = GFX_new( 0 );
  q = GFX_new( 0 );
  table = (GFX**)calloc(max, sizeof(GFX*));
  for( i=0; i<max; i++)
    table[i] = GFX_new( 1 );
  table[0]->degree = 1;
  table[0]->a[0] = 1;
  table[0]->a[1] = 0;
  fprintf(fp, "%x,", GF_BASE);
  counter = 1;
  
  for( i=1; counter<max; i++ ){
    int _deg, j, k, l, is_irred;
    
    l = i;
    _deg = 0;
    while (l) {
      l >>= GF_BASE_DIGITS;
      _deg++;
    }
    if( _deg > deg ){
      i = 0;
      deg = _deg;
    }
    is_irred = 1;
    poly->degree = deg;
    poly->a = (unsigned char*)realloc(poly->a, (deg+1)*sizeof(unsigned char));
    poly->a[0] = 1; /** we consider only monic polynomials **/
    for( k=deg, l=i; k>=1; k--, l>>=GF_BASE_DIGITS )
      poly->a[k] = (unsigned char)GF_getBits( l );
    for( j=0; table[j]->degree <= deg/2 && j<counter ; j++ ){
      GFX_div(poly, table[j], q, r);
      if(GFX_isZero(r)){
	is_irred = 0;
	break;
      }
    }
    if( is_irred ){
      GFX_copy(poly, table[counter]);
      fprintf(fp, "%x,",i+(0x01 << GF_BASE_DIGITS*deg));
      counter++;
    }
  }
  
  GFX_del(q);
  GFX_del(r);
  
  // delete irreducible polynomials.
  for( i = 0; i < counter; i++ )
    GFX_del( table[i] );
  GFX_del( poly );
  
  // close the output file.
  fclose(fp);

  return 0;
}
