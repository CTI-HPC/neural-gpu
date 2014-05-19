//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);

        // Recibimos el arreglo y lo guardamos en tmp.
        float *tmp;
        tmp = (float*)request.data();
        for (int j = 0; j < 10; j++) {
            std::cout << "Received " << tmp[j]  << std::endl;
        }

        //  Enviamos otro arreglo de vuelta
        float b[10];
        for (int i = 0; i < 10; i++) {
            b[i] = (float)2*i;
        }

        zmq::message_t reply (10*sizeof(float));
        memcpy(reply.data(),b,10*sizeof(float));
        socket.send (reply);
    }
    return 0;
}
