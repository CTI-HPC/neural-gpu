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

TARGETS = main

all: $(TARGETS)
main: main.o cpu-map.o gpu-map.o
main.o: main.cpp cpu-map.hpp gpu-map.hpp
cpu-map.o: cpu-map.cpp cpu-map.hpp
gpu-map.o: gpu-map.cu gpu-map.hpp
	$(NVCC) $(INCLUDEFLAGS) $< -c -o $@

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean
