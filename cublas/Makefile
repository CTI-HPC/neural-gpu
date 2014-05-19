BIN = cublas-mv cuda-mv

all: $(BIN)

cublas-mv.o: cublas-mv.cu
	nvcc -c $< -lcublas

cublas-mv: cublas-mv.o
	nvcc $< -o $@ -lcublas

cuda-mv.o: cuda-mv.cu
	nvcc -c $<

cuda-mv: cuda-mv.o
	nvcc $< -o $@

clean:
	rm -f $(BIN) *.o
