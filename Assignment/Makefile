#Inclusions for CUDA
INC := -I${CUDA_HOME}/include
LIB := -L${CUDA_HOME}/lib64 -lcudart -lcuda -lcurand

GCC = g++
NVCC = ${CUDA_HOME}/bin/nvcc

NVCCFLAGS = -O3 -arch=sm_35 --ptxas-options=-v -Xcompiler -Wextra -lineinfo

GCC_OPTS =-O3 -Wall -Wextra $(INC)

#Inclusions for openmp
CC = gcc
CFLAGS = -O3 -mavx -std=c99 -Wall -Wextra -pedantic -fopenmp 
LIBS = -lm

#Output filenames
EXCFILE1 = reduction
EXCFILE2 = reduction_atomic
EXCFILE3 = reduction_omp

#make functions
all: clean reduction reduction_atomic

reduction_omp: reduction_omp.c Makefile
	$(CC) $(CFLAGS) -o $(EXCFILE3) reduction.c $(LIBS)

reduction: reduction.cu Makefile
	$(NVCC) -o $(EXCFILE1) reduction.cu $(LIB) $(NVCCFLAGS) 

reduction_atomic: reduction_atomic.cu Makefile
	$(NVCC) -o $(EXCFILE2) reduction_atomic.cu $(LIB) $(NVCCFLAGS)

clean:	
	rm -f *.o $(ANALYZE)



