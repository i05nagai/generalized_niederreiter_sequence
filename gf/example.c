#include<stdlib.h>
#include<unistd.h>
#include"n_lds_GF.h"
#include<time.h>

int main( int ac, char **av ){
	
  int i;
  char c;
  double *v;
  int dim = 6, SeqType = 2;
  unsigned long jump = 1, num = 20000;
  unsigned long seed = 1;
  int flag_g = 1, flag_l = 1, flag_s = 1;
  unsigned char base = 16;

  clock_t start, end;
  
  while((c = getopt(ac, av,"b:d:gj:ln:r:st:"))!=EOF){
    switch(c){
    case 'b':
      base = atoi(optarg); break;
    case 'd':
      dim = atoi(optarg); break;
    case 'g':
      flag_g = 1; break;
    case 'j':
      jump = atoi(optarg);
      break;
    case 'l':
      flag_l = 1; break;
    case 'n':
      num = atoi(optarg); break;
    case 'r':
      seed = atoi(optarg); break;
    case 's':
      flag_s = 1; break;
    case 't':
      SeqType = atoi(optarg); break;
    default:
      break;
    }
  }

  v = (double*)malloc(dim*sizeof(double));
  LDS_initialize(base, dim, v, SeqType, jump, seed, flag_g, flag_l, flag_s);

  printf("high-dimension sequence.\n");
  printf("base = %d, dim = %d, SeqType = %d, jump = %lu, seed = %lu, num = %lu\n", base, dim, SeqType, jump, seed,  num);
  printf("flag_g = %d, flag_l = %d, flag_s = %d\n", flag_g, flag_l, flag_s);

  start = clock();
  for(i=0;i<num;i++){
    LDS_GF( v );
  }
  end = clock();
  printf("time\t:\t%d\n", (int)(end-start));

  return 0;

}
