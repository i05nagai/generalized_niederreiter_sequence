#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"GF16.h"

static void division(int a, int b, int *q, int *r){
  int tq = 0, tr = a;

  while( tr >= b ){
    tr -= b;
    tq++;
  }
  *q = tq;
  *r = tr;
}

void GF16_matrix_gen(int dim, GF16_MATRIX *g_m, unsigned long seed, int flug_g, int flug_l, int flug_s){

  int i,j,k,l;
  GF16_MATRIX t_g_m, r_m;
  FILE *fp;

  fp = fopen("IP16","r");
  if(fp == NULL){
    fprintf(stderr,"can't open IP16.\n");
    exit(1);
  }
  
  for( i = 0; i < dim; i++ ){
    int IP_deg = 1;
    int Q, r, R; 
    int IP_value;
    GF16X *IP, *X, *QX, *RX;
    
    X = GF16X_new(0);
    QX = GF16X_new(0);
    RX = GF16X_new(0);
    
    fscanf(fp, "%x,", &IP_value);
    while( IP_value >> BITS_GF16*(IP_deg+1) != 0 )
      IP_deg++;
    IP = GF16X_new( IP_deg );
    
    for( j = 0; j <= IP_deg ; j++ )
      IP->a[IP_deg - j] = (char)GF16_get_bits(IP_value >> BITS_GF16*j);
    for( j = 0; j < MAXDIGITS_GF16; j++){
      division(j, IP_deg, &Q, &r);
      GF16X_set_zero( X );
      X->a[0] = 1;
      /* switch 1 : generalized niederriter sequence */
      if(flug_g)
	R = IP_deg - 1 - r;
      else
	R = r;
      /* end switch 1 */
      GF16X_mult_x_n( X, R );
      /* switch 2 : addition to lower term */
      if(flug_l)
	for( k = 1; k <= R; k++ )
	  X->a[k] = GF16_rand(seed);
      /* end switch 2 */
      GF16X_mult_x_n( X, MAXDIGITS_GF16 );
      for( k = 0; k < Q+1; k++ ){
	if( X->degree < IP_deg ){
	  GF16X_set_zero( QX );
	  break;
	}
	GF16X_div(X, IP, QX, RX);
	GF16X_copy(QX,X);
      }
      
      for( k=0; k<MAXDIGITS_GF16 - QX->degree-1; k++)
	t_g_m[j][k] = 0;
      for( k=MAXDIGITS_GF16-QX->degree-1;k<MAXDIGITS_GF16; k++)
	t_g_m[j][k] = QX->a[k - MAXDIGITS_GF16 +QX->degree + 1];
    }
    
    GF16X_del( X );
    GF16X_del( QX );
    GF16X_del( RX );
    GF16X_del( IP );
    
    /* switch 3 : scramble */
    if(flug_s)
      GF16_scramble(seed,t_g_m,g_m[i]);
    else{
      for( j = 0; j < MAXDIGITS_GF16; j++ )
	for( k = 0;k < MAXDIGITS_GF16; k++ )
	  g_m[i][j][k] = t_g_m[j][k];
    }
    /* end switch 3 */
    
  }/* for i */
  fclose(fp);
}

