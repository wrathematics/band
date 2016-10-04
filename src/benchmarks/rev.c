#include "../utils/rev.h"

#include "../utils/internal/gen.h"
#include "../utils/internal/timer.h"


int main()
{
  const int nreps = 100;
  double *x;
  
  printf("\n");
  
  for (int n=500; n<3000; n+=1000)
  {
    x = gen_runif2(n*n);
    
    // printf("n=%d\t", n);
    TIMER(reverse_mat(n, n, x), nreps);
    
    free(x);
  }
  
  return 0;
}
