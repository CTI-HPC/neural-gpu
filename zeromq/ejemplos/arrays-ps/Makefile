CC=g++
CXXFLAGS=-Wall -lzmq


all: hwclient hwserver

client: client.cpp
	$(CC) $(CXXFLAGS)  $< -o $@

server: server.cpp
	$(CC) $(CXXFLAGS)  $< -o $@

clean:
	@rm -rf hwclient hwserver

.PHONY: all clean
