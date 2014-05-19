# Change this variable as needed.
CUDA_HEADER_PATH = /opt/cuda/include/

INTEL64 = /opt/software/intel/composer/mkl/lib/intel64

CXX = g++
CXXFLAGS = -Wall -I$(CUDA_HEADER_PATH)
LDFLAGS = -lstdc++ -lm -lcublas -lgomp -lblas

BIN = GPUController.o TestUtils.o serial-forward-pass.o gpu-forward-pass.o mkl-forward-pass.o

all: $(BIN)

GPUController.o: GPUController.cpp GPUController.hpp
TestUtils.o: TestUtils.cpp TestUtils.hpp
serial-forward-pass.o: serial-forward-pass.cpp serial-forward-pass.hpp

mkl-forward-pass.o: mkl-forward-pass.cpp mkl-forward-pass.hpp
	g++ \
	  -L$(INTEL64) -Wl,-R$(INTEL64) \
	  -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread \
	  -c $<

gpu-forward-pass.o: gpu-forward-pass.cu gpu-forward-pass.hpp
	nvcc  --ptxas-options=-v -c $<

clean:
	@rm -vf $(BIN)

.PHONY: all clean
