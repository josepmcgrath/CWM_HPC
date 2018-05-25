#include <stdio.h>
#include <stdlib.h>

//include openMP library
#include "omp.h"

#define NUM_ELS 100000

int main() {
	
    float random_array[NUM_ELS];
    float sum=0;
    int i;

    //timing variables
      double time_start, time_end;

    // initialize values
      for(i=0; i<NUM_ELS; i++) {
          random_array[i] = ((float)rand())/((float)RAND_MAX);
      }

    //start time
       time_start = omp_get_wtime ( );

    #pragma omp parallel default(none) shared(random_array, sum) private(i)
    {  
      #pragma omp for reduction(+:sum)
      for(i=0; i<NUM_ELS; i++) {
          sum+=random_array[i];
      }
    }
    
    // end time
      time_end = omp_get_wtime ( );
    
    printf(" process time      = %e s\n", time_end - time_start);
    float average = sum / (float)NUM_ELS;
    printf("Average: %f\n", average);

    return(0);
}
