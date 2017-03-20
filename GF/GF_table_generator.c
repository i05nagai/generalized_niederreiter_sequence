#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// prototype declaration
static unsigned char mult(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);

// main
int main(void){

  int i, j;
  int n;
  unsigned char *multTable;
  unsigned char base[] = {4,16};
  unsigned char baseDigits[] = {2,4};
  unsigned char irredPoly[] = {0x07,0x1f};
  
  FILE *fp;
  
  // open a output file.
  fp = fopen("GF_table","w");
  if( fp == NULL ){
    fprintf(stderr,"can't open GF_table.\n");
    exit(1);
  }

  // create GF4 and GF16 table.
  for( n=0; n<2; n++ ){

    // allocate memory for multTable.
    multTable = (unsigned char *)malloc(sizeof(unsigned char)*base[n]*base[n]);

    // comment
    fprintf(fp, "************* base = %d *************\n", base[n]);
    fprintf(fp, "\n");

    // multiplycation for table
    fprintf(fp, "multiplication:\n");
    for( i=0; i<base[n]; i++ ){
      for( j=0; j<base[n]; j++ ){
	multTable[ base[n]*i + j ] = mult(base[n], i, j, baseDigits[n], irredPoly[n]);
	fprintf(fp, "%3d", multTable[ base[n]*i + j ]);
      }
      fprintf(fp, "\n");
    }
    fprintf(fp, "\n");

    // multiplycation for sequence
    for( i=0; i<base[n]; i++ )
      for( j=0; j<base[n]; j++ )
	fprintf(fp, "%d,", multTable[ base[n]*i + j ]);
    fprintf(fp, "\n\n");
  
    // inverse
    fprintf(fp, "inverse:\n");

    {
      // i = 0
      fprintf(fp, "0,");

      // i != 0
      for( i=1; i<base[n]; i++ )
	for( j=1; j<base[n]; j++ )
	  if( multTable[ base[n]*i + j ] == 1 )
	    fprintf(fp, "%d,", j);
      fprintf(fp, "\n\n");
    }
    
    // free temporaly memory.
    free( multTable );

  }

  // close output file.
  fclose( fp );

  return 0;

}

static unsigned char mult(unsigned char base, unsigned char i, unsigned char j, unsigned char baseDigits, unsigned char irredPoly){

  int a, b, c;
  int k,l;

  // a, b and c is supposed to polynomial.
  a = i;
  b = j;
  c = 0;

  // c = a * b
  for( k=0; k<baseDigits; k++ ){
    c ^= ( a & 0x01 ) * b;
    a >>= 1;
    b <<= 1;
  }

  // c = c mod irredPoly
  while( c >= base ){

    // get baseDigits of c
    l=0;
    while( (c >> l) != 0 )
      l++;

    // c = c - irredPoly * x^(l-bits-1)
    if( l > baseDigits )
      c ^= irredPoly << (l - baseDigits - 1);
    else
      break;

  }
  
  // return
  return c;
  
}
