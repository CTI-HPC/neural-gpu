// Server
#include <zmq.hpp>
#include <iostream>
#include <unistd.h>

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind ("tcp://*:5000");

    while (true) {
        float b[10];
        for (int i = 0; i < 10; i++) {
            b[i] = (float)i;
        }

        sleep(1);

        std::cout << "Enviando mensaje..." << std::endl;
        zmq::message_t msg (10*sizeof(float));
        memcpy(msg.data(),b,10*sizeof(float));
        socket.send (msg);
    }
    return 0;
}
