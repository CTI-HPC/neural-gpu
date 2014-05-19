#include "gpu-controller-service.hpp"

bool init(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    if (!init(argc,argv)){
        return 1;
    }

    // GPUController init
    GPUController c(N, H, M);
    c.set_method(method);
    c.set_activation(activation);
    c.load_parameters(path);

    // ZeroMQ configuration
    zmq::context_t context(1);
    zmq::socket_t receiver(context, ZMQ_REP);
    zmq::socket_t sender(context, ZMQ_REQ);

    // ZeroMQ connections
    receiver.bind("tcp://127.0.0.1:5000");
    sender.connect("tcp://127.0.0.101:5050");

    // ZeroMQ  messages
    zmq::message_t input_request;
    zmq::message_t input_reply;
    zmq::message_t output_request;
    zmq::message_t output_reply;

    double time_tot_start, time_tot_end;
    //double gpu_time[1000];

    cout << "Controller ready" << endl;
    time_tot_start = omp_get_wtime();
    while (msg_num < 1000){

        // Receiving message from «input-sender»
        assert(receiver.recv(&input_request));

        // Obtaining received message data
        data = (float*)input_request.data();
        msg.size = (int)input_request.size()/sizeof(float);
        msg.data = (float*)malloc(msg.size*sizeof(float));
        for (int i = 0; i < msg.size; i++) msg.data[i] = data[i];

        // Sending data to GPU/CPU device
        //time_tot_start = omp_get_wtime();
        c.push(msg.data,msg.size);
        //time_tot_end = omp_get_wtime();

        //gpu_time[msg_num] = time_tot_end - time_tot_start;

        // Obtaining output vector and copying it to a zmq-message
        output = c.get_output();
        output_request.rebuild(M*sizeof(float));
        memcpy((void*)output_request.data(), output, M*sizeof(float));

        // Sending output vector to the «output-receiver»
        assert(sender.send(output_request));

        // Receiving answer from «output-receiver»
        assert(sender.recv(&output_reply));

        // Configuring and sendind an answer to «input-sender»
        input_reply.rebuild(1);
        memcpy ((void *)input_reply.data(), "1", 1);
        assert(receiver.send(input_reply));

        msg_num++;
    }
    time_tot_end = omp_get_wtime();
    cout << "Average GPU calculation: " << (time_tot_end - time_tot_start)/(double)1e6 |
<< "[µs]" <<endl;

    // Printing values
    //stringstream ss;
    //ss << path.substr(15,path.length()-15) << "-gpu";
    //string output_file = ss.str();
    //std::ofstream file(output_file.c_str());
    //int i;
    //for (i = 0; i < 1000; i++) {
    //    file << gpu_time[i] << endl;
    //}
    //file.close();
    // END



    return 0;
}


bool init(int argc, char *argv[]){
    method = 0;
    activation = 1;
    iter = 1;
    th = 128;
    msg_num = 0;

    if(!check_flags(argc,argv,path,method,activation, iter,th)){
        return false;
    }

    parse_info_file(path,N,H,M);
    return true;
}
