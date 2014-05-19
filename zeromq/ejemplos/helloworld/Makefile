CC=g++
CXXFLAGS=-Wall -lzmq


all: client server

client: client.cpp
	$(CC) $(CXXFLAGS)  $< -o $@

server: server.cpp
	$(CC) $(CXXFLAGS)  $< -o $@

clean:
	@rm -rf client server

.PHONY: all clean
