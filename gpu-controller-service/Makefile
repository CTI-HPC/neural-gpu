CUDA_HEADER_PATH = /opt/cuda/include/
CONTROLLER_PATH = ../gpu-controller/
INTEL64 = /opt/software/intel/composer/mkl/lib/intel64

CXX = g++
CXXFLAGS = -Wall -I$(CUDA_HEADER_PATH)
LDFLAGS =  -lcublas -fopenmp -lzmq -lboost_program_options \
-L$(INTEL64)  -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 -lpthread 

BIN = controller input-sender gpu-controller-service output-receiver
OBJ_CONTROLLER = $(CONTROLLER_PATH)GPUController.o $(CONTROLLER_PATH)TestUtils.o $(CONTROLLER_PATH)serial-forward-pass.o $(CONTROLLER_PATH)gpu-forward-pass.o $(CONTROLLER_PATH)mkl-forward-pass.o

all: $(BIN)

controller:
	make -C $(CONTROLLER_PATH)

input-sender: input-sender.cpp $(OBJ_CONTROLLER)
gpu-controller-service: gpu-controller-service.cpp gpu-controller-service.hpp $(OBJ_CONTROLLER)

clean:
	@rm -vf *.o $(BIN)

.PHONY: all clean
