#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"GF4.h"

int main ( int ac, char **av ){
  	int c;
	extern int optind;
	extern char *optarg;
	int max = MAXDIM, counter, i, deg = 1;
	GF4X **table, *poly,*q,*r;
	FILE *fp;
	
	fp = fopen("IP4","w");
	if(fp==NULL){
		printf("can't open IP4.\n");
		exit(1);
	}
	
	while((c = getopt(ac, av,"m:h"))!=EOF){
    	switch(c){
    	case 'm':
    		max = atoi(optarg);
    		if( max <= 0 ){
				fprintf(stderr,"max is needed to be a natural number.\n!");
				exit(1);
			}
    		break;
    	case 'h':
    		fprintf(stderr, "usage: GF4_gen_irred_poly, -m <max num>\n");
    		exit(1);
    		break;
    	default:
    		break;
		}
	}
  	
	poly = GF4X_new( 0 );
	r = GF4X_new( 0 );
	q = GF4X_new( 0 );
	table = (GF4X**)calloc(max, sizeof(GF4X*));
	for( i=0; i<max; i++)
		table[i] = GF4X_new( 1 );
	table[0]->degree = 1;
	table[0]->a[0] = 1;
	table[0]->a[1] = 0;
	fprintf(fp, "%x,",BASE_GF4);
	counter = 1;
	
	for( i=1; counter<max; i++ ){
		int _deg, j, k, l, is_irred;
		
		l = i;
		_deg = 0;
		while (l) {
			l >>= BITS_GF4;
			_deg++;
		}
		if( _deg > deg ){
			i = 0;
			deg = _deg;
		}
		is_irred = 1;
		poly->degree = deg;
		poly->a = (char*)realloc(poly->a, (deg+1)*sizeof(char));
		poly->a[0] = 1; /** we consider only monic polynomials **/
  		for( k=deg, l=i; k>=1; k--, l>>=BITS_GF4 )
			poly->a[k] = (char)GF4_get_bits(l);
		for( j=0; table[j]->degree <= deg/2 && j<counter ; j++ ){
			GF4X_div(poly, table[j], q, r);
			if(GF4X_is_zero(r)){
				is_irred = 0;
				break;
			}
		}
		if( is_irred ){
			GF4X_copy(poly, table[counter]);
			fprintf(fp, "%x,",i+(0x01 << BITS_GF4*deg));
			counter++;
		}
	}
	
	GF4X_del(q);
	GF4X_del(r);

	for( i = 0; i < counter; i++ )
		GF4X_del( table[i] );
	GF4X_del( poly );

	fclose(fp);
}
