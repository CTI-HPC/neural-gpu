NVCC = nvcc
CC = g++
CXXFLAGS = -Wall $(INCLUDEFLAGS) -fopenmp

# poner la ubicación correcta de CUDA en su equipo
CUDA = /usr/local/cuda
#CUDA = /opt/cuda

CUDAHEADERS = $(CUDA)/include
INCLUDEFLAGS = -I $(CUDAHEADERS)

# si su equipo es de 32 bits, quitar el primer ítem
LDFLAGS += -L$(CUDA)/lib64 -L$(CUDA)/lib
LDFLAGS += -lm -lgomp -lcudart

all: integral integral-cpu

integral-cpu: integral-cpu.cpp

integral: integral.cu
	$(NVCC) $(CUFLAGS) $(INCLUDEFLAGS) $< -o $@

clean:
	@rm -vf integral-cpu integral

.PHONY: all clean

