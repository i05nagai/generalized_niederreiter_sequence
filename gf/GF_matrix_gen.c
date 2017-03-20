#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"GF.h"

static void division(int a, int b, int *q, int *r){
  int tq = 0, tr = a;
  
  while( tr >= b ){
    tr -= b;
    tq++;
  }
  *q = tq;
  *r = tr;
}

void GF_matrix_gen(int dim, GF_MATRIX *g_m, unsigned long seed, int flag_g, int flag_l, int flag_s){
  
  int i,j,k;
  GF_MATRIX t_g_m;
  FILE *fp;
  unsigned char base, baseDigits, matrixSize;
  char filename[5];
  
  // initialize
  base = getBase();
  baseDigits = getBaseDigits();
  matrixSize = getMatrixSize();
  for( i=0; i<dim; i++ )
    g_m[i] = GF_newMatrix();
  t_g_m = GF_newMatrix();
  
  // open input file.
  sprintf(filename, "IP%d", base);
  fp = fopen(filename, "r");
  if( fp == NULL ){
    fprintf(stderr, "can't open IP%d.\n", base);
    exit(1);
  }
  
  for( i=0; i<dim; i++ ){
    int IP_deg = 1;
    int Q, r, R; 
    int IP_value;
    GFX *IP, *X, *QX, *RX;
    
    X = GFX_new(0);
    QX = GFX_new(0);
    RX = GFX_new(0);

    fscanf(fp, "%x,", &IP_value);
    while( IP_value >> baseDigits*(IP_deg+1) != 0 )
      IP_deg++;
    IP = GFX_new( IP_deg );
    for( j = 0; j <= IP_deg ; j++ )
      IP->a[IP_deg - j] = (unsigned char)GF_getBits(base, IP_value >> baseDigits*j);
    for( j=0; j<matrixSize; j++ ){
      division(j, IP_deg, &Q, &r);
      GFX_setZero( X );
      X->a[0] = 1;
      
      /* switch 1 : generalized niederriter sequence */
      if(flag_g)
	R = IP_deg - 1 - r;
      else
	R = r;
      
      /* end switch 1 */
      GFX_mult_x_n( X, R );
      
      /* switch 2 : addition to lower term */
      if(flag_l)
	for( k=1; k<=R; k++ )
	  X->a[k] = GF_rand(seed);
      
      /* end switch 2 */
      GFX_mult_x_n( X, matrixSize );
      for( k=0; k<Q+1; k++ ){
	if( X->degree < IP_deg ){
	  GFX_setZero( QX );
	  break;
	}
	GFX_div(X, IP, QX, RX);
	GFX_copy(QX,X);
      }

      for( k=0; k<getMatrixSize() - QX->degree-1; k++)
	t_g_m[j][k] = 0;
      for( k=matrixSize-QX->degree-1; k<matrixSize; k++)
	t_g_m[j][k] = QX->a[k - matrixSize + QX->degree + 1];
    }
    
    GFX_del( X );
    GFX_del( QX );
    GFX_del( RX );
    GFX_del( IP );
    
    /* switch 3 : scramble */
    if(flag_s)
      GF_scramble(seed, t_g_m, g_m[i]);
    else{
      for( j=0; j<matrixSize; j++ )
	for( k=0; k<matrixSize; k++ )
	  g_m[i][j][k] = t_g_m[j][k];
    }
    /* end switch 3 */

  }/* for i */
  
  fclose(fp);
}

