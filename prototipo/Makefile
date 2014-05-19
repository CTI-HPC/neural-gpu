CC = g++
LDFLAGS = -Wall -lgomp
NVCCFLAGS = -lcublas -lgomp
BIN = test-red-serial test-ibm test-large-case neural-gpu parallel-test-case

all: $(BIN)

ibm.o: ibm.cpp ibm.hpp
test-ibm.o: test-ibm.cpp ibm.hpp
large-case.o: large-case.cpp large-case.hpp
test-large-case.o: test-large-case.cpp large-case.hpp
red-serial.o: red-serial.cpp ibm.hpp

test-ibm: ibm.o test-ibm.o
test-red-serial: ibm.o red-serial.o
test-large-case: large-case.o test-large-case.o red-serial.o

neural-gpu.o: neural-gpu.cu
	nvcc -c $<

neural-gpu: neural-gpu.o ibm.o
	nvcc $^ -o $@

parallel-test-case.o: parallel-test-case.cu
	nvcc -c $< $(NVCCFLAGS)

parallel-test-case: parallel-test-case.o ibm.o red-serial.o large-case.o
	nvcc $^ -o $@ $(NVCCFLAGS)

clean:
	rm -f $(BIN) *.o
