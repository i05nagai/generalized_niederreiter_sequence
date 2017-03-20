#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"n_lds_GF4.h"

int main( int ac, char **av ){
	
  int i,j;
  char c;
  double *v,w;
  int dim = 6, Seq_type = 0;
  unsigned long jump = 1, num = 20;
  unsigned long seed = 1;
  int flug_g = 0, flug_l = 0, flug_s = 0;
  
  while((c = getopt(ac, av,"d:gj:ln:r:st:"))!=EOF){
    switch(c){
    case 'd':
      dim = atoi(optarg); break;
    case 'g':
      flug_g = 1; break;
    case 'j':
      jump = atoi(optarg);
      break;
    case 'l':
      flug_l = 1; break;
    case 'n':
      num = atoi(optarg); break;
    case 'r':
      seed = atoi(optarg); break;
    case 's':
      flug_s = 1; break;
    case 't':
      Seq_type = atoi(optarg); break;
    default:
      break;
    }
  }
  
  v = (double*)malloc(dim*sizeof(double));
  printf("high-dimension sequence.\n");
  printf("base = 4, dim = %d, Seq_type = %d, jump = %lu, seed = %lu, num = %lu\n", dim, Seq_type, jump, seed,  num);
  printf("flug_g = %d, flug_l = %d, flug_s = %d\n", flug_g, flug_l, flug_s);
  for(i=0;i<num;i++){
    LDS_GF4(dim, v, Seq_type, jump, seed, flug_g, flug_l, flug_s);
    for(j=0;j<dim;j++)
      printf("%12.8lf",v[j]);
      printf("\n");
  }
  /*printf("\n");
  
  printf("Box-Muller\n");
  printf("base = 4, dim = %d, Seq_type = %d, jump = %lu, seed = %lu, num = %lu\n", dim, Seq_type, jump, seed,  num);
  printf("flug_g = %d, flug_l = %d, flug_s = %d\n", flug_g, flug_l, flug_s);
  for(i=0;i<num;i++){
    LDS_Gauss_GF4(dim, v, Seq_type, jump, seed, flug_g, flug_l, flug_s);
    for(j=0;j<dim;j++)
      printf("%12.8lf",v[j]);
      printf("\n");
      }*/

  return 0;

}
