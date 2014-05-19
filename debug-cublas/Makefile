CUDA_HEADER_PATH = /opt/cuda/include/
CC = gcc
CFLAGS = -Wall -I$(CUDA_HEADER_PATH)
LDFLAGS = -lm -lcublas

BIN = mult-test mkl-test

all: $(BIN)
mkl-test: mkl-test.c
	icc \
	  -L/opt/software/intel/composer/mkl/lib/intel64 \
	  -Wl,-R/opt/software/intel/composer/mkl/lib/intel64 \
	  -lmkl_intel_lp64 -lmkl_intel_thread \
	  -lmkl_core -liomp5 -lpthread \
	   $< -o $@
clean:
	@rm -rfv $(BIN)

