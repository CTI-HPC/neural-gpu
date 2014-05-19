# Change this variable as needed.
CUDA_HEADER_PATH = /opt/cuda/include/
CONTROLLER_PATH = ../gpu-controller/

CXX = g++
CXXFLAGS = -Wall -I$(CUDA_HEADER_PATH)
LDFLAGS = -lm -lcublas -lgomp

BIN = gpu-controller profile
OBJ_CONTROLLER = $(CONTROLLER_PATH)GPUController.o $(CONTROLLER_PATH)serial-forward-pass.o $(CONTROLLER_PATH)gpu-forward-pass.o

PBS_OUTPUT = $(shell ls | egrep '[.][oe][[:digit:]]+$$')

all: $(BIN)

gpu-controller:
	make -C ../gpu-controller

profile.o: profile.cpp

profile: profile.o $(OBJ_CONTROLLER)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

clean:
	@rm -vf *.o $(BIN)
	@rm -vf $(PBS_OUTPUT)

.PHONY: all clean
