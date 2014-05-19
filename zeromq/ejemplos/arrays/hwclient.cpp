#include <zmq.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect ("tcp://localhost:5555");

        // Creamos arreglo para enviar
        float a[10];
        for (int i = 0; i < 10; i++) {
            a[i] = (float)2*i-1;
        }

        // Creamos el mensaje zmq con el tamaño del arreglo
        zmq::message_t request(10*sizeof(float));
        // Copiamos datos
        memcpy(request.data(),a,10*sizeof(float));

        // Envio del mensaje
        std::cout << "Sending " << "..." << std::endl;
        socket.send (request);

        //  Get the reply.
        zmq::message_t reply;
        float *tmp;
        // Recibimos mensaje y guardamos en reply
        socket.recv (&reply);
        // Cast de void* a float*
        tmp = (float*)reply.data();

        // Imprimimos el arreglo
        for (int j = 0; j < 10; j++) {
            std::cout << "Received " << tmp[j]  << std::endl;
        }
    return 0;
}
