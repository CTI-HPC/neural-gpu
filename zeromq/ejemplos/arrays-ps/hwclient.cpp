// Client
#include <zmq.hpp>
#include <iostream>

int main ()
{
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_SUB);

    socket.connect ("tcp://localhost:5000");
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::message_t reply;
    float *tmp;

    socket.recv (&reply);
    tmp = (float*)reply.data();

    for (int j = 0; j < 10; j++) {
        std::cout << "Received " << tmp[j]  << std::endl;
    }
    return 0;
}
