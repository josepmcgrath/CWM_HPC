// Uses cuRAND to generate a normal distribution of numbers

// Include necessary files
#include <cuda.h>
#include <curand.h>
#include <stdio.h>

int main(void) {
  // Allocate pointers for host and device memory
    float *h_output;
    float *d_output;

  // Determine number of random numbers using user input
    int number_of_random_nums;
    printf("Enter the number of random numbers to generate: ");
    scanf("%d", &number_of_random_nums);

  // malloc() host memory (in RAM)
    
