#include "GF4.h"
/** #include "mt19937ar-clok.h" **/
#include <gsl/gsl_rng.h>

char GF4_mult_table[] = {0,0,0,0,0,1,2,3,0,2,3,1,0,3,1,2};
char GF4_inv_table[] = {0,1,3,2};

char GF4_power(char a, char b){
	char y, z;
	z = 1;
	y = a;
	while (b >= 1){
		if ( b & 1 )
			z = GF4_mult(y,z);
		b >>= 1;
		y = GF4_mult(y,y);
	}
	return z;
}

static int GF4_rand_init = 1;
static gsl_rng *mt19937;
char GF4_rand(unsigned long seed){
  if(GF4_rand_init){
    /** int_genrand(seed); **/
    mt19937 = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(mt19937, seed);
    GF4_rand_init = 0;
  }
  /** v = tp*genrand_real2(); **/
  return BASE_GF4*gsl_rng_uniform(mt19937);
}

void GF4_rand_initialize(void){
  GF4_rand_init = 1;
}
