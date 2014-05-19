#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[]) {
    // ZeroMQ configuration
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_REP);
    receiver.bind("tcp://127.0.0.101:5050");
    // End ZeroMQ configuration

    zmq::message_t output_request;
    zmq::message_t reply;


    cout << "Output receiver ready" << endl;
    while (1){
       assert(receiver.recv(&output_request));
       // float *ddd;
       // ddd = (float*)output_request.data();
       //for (int i = 0; i < (int)output_request.size()/sizeof(int); i++) {
       //     cout << i << " " << ddd[i] << endl;
       //}
       memcpy((void *) reply.data (), "1", 1);

       assert(receiver.send(reply));
    }

    return 0;
}
