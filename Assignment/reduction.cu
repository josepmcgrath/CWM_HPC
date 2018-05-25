#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>

// Include cuda functions
#include <cuda.h>
#include <curand.h>

// Include timing functions
#include <sys/time.h>
#define MILLION 1000000.0

#define MAX_THREADS 1024

__global__ void reduction(float *d_input, float *d_output, int num_els)
{
    // Allocate shared memory

    __shared__  float smem_array[MAX_THREADS];

    int tid = threadIdx.x;
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    // first, each thread loads data into shared memory
    if (index < num_els) {
      smem_array[tid] = d_input[index];
    } else {
      smem_array[tid] = 0;
    }
    // next, we perform binary tree reduction

    for (int d = blockDim.x/2; d > 0; d /= 2) {
      __syncthreads();  // ensure previous step completed 
      if (tid<d)  smem_array[tid] += smem_array[tid+d];
    }

    // finally, first thread puts result into global memory

    if (tid==0) d_output[blockIdx.x] = smem_array[0];
}

double wall_clock_time (void) {

  double secs;
  struct timeval tp;

  gettimeofday (&tp,NULL);
  secs = (MILLION * (double) tp.tv_sec + (double) tp.tv_usec) / MILLION;
  return secs;

}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////

int main( int argc, const char** argv) 
{
    int num_els, num_threads, mem_size, num_blocks;

    float *h_data;
    float *d_input, *d_output;
    
    // timing variables
     
    double time_start, time_end;
    
    // Take user input for number of random numbers
    
    printf("Enter a number of random numbers: ");
    scanf("%d", &num_els);

    // initialise card

    num_threads = MAX_THREADS;
    mem_size    = sizeof(float) * num_els;
    num_blocks = ((num_els % MAX_THREADS) == 0) ? (num_els / MAX_THREADS) : (num_els / MAX_THREADS + 1);
    
    // allocate host memory to store the input data
    // and initialize to integer values between 0 and 1000

    h_data = (float*) malloc(mem_size);
      
    // allocate device memory input and output arrays

    cudaMalloc((void**)&d_input, mem_size);
    cudaMalloc((void**)&d_output, (num_blocks * sizeof(float)));

    // Use cuRAND to generate input data

      // Create pseudo-random number generator
        curandGenerator_t gen;
        curandCreateGenerator(&gen, CURAND_RNG_PSEUDO_DEFAULT);

      // Set the generator options
        curandSetPseudoRandomGeneratorSeed(gen, 1234ULL);

      // Generate the randoms
        curandGenerateNormal(gen, d_input, num_els, 0.0f, 1.0f);


    // copy host memory to device input array

   // cudaMemcpy(d_input, h_data, mem_size, cudaMemcpyHostToDevice);

    // execute the kernel
    
      // start time
      time_start = wall_clock_time ( );

    reduction<<<num_blocks,num_threads>>>(d_input,d_output, num_els);

      // end time
       time_end = wall_clock_time ( );

    // copy result from device to host

    cudaMemcpy(h_data, d_output, num_blocks * sizeof(float), cudaMemcpyDeviceToHost);
    
    // Sum results from all blocks
    
    for (int i = 1; i < num_blocks; i++) {
      h_data[0] += h_data[i];
    }

    // check results
    printf(" process time      = %e s\n", time_end - time_start);
    printf("Total sum: %f\n", h_data[0]);
    printf("reduction error = %f\n",h_data[0]/num_els);

    // cleanup memory

    free(h_data);
    cudaFree(d_input);
    cudaFree(d_output);
    curandDestroyGenerator(gen);
    
    // CUDA exit -- needed to flush printf write buffer

    cudaDeviceReset();
}

