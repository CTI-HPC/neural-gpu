#include <zmq.hpp>
#include <string>
#include <iostream>
#include <omp.h>
#include <boost/program_options.hpp>
#include "../gpu-controller/TestUtils.hpp"
using namespace std;
namespace po = boost::program_options;

string check_input_flags(int argc, char *argv[]);

int main(int argc, char *argv[]) {

    // Initialization
    string path = check_input_flags(argc, argv);
    string filename;
    if (path.empty()){
        return 0;
    }
    vector<float> input_vector;
    load_matrix(input_vector,path+"input.txt");
    if (input_vector.empty()){
        cerr << "Empty input vector: No such file or directory" << endl;
    }
    int size = (int)input_vector.size();
    int msg_num = 0;
    //double time_msgs[1000];
    // End initialization

    // ZMQ Configuration
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);
    socket.connect("tcp://127.0.0.1:5000");
    // End ZMQ Configuration

    zmq::message_t input_request, input_reply;
    //double time_msg_start, time_msg_end;
    double time_tot_start, time_tot_end;

    time_tot_start = omp_get_wtime();
    cout << "Input Sender starting..." << endl;
    while(msg_num < 1000){
        //time_msg_start = omp_get_wtime();

        input_request.rebuild(size*sizeof(float));
        memcpy ((void *) input_request.data(), &input_vector[0], size*sizeof(float));

        socket.send (input_request);

        input_reply.rebuild(1);
        socket.recv (&input_reply);

        msg_num++;
        //time_msg_end = omp_get_wtime();

        //time_msgs[msg_num] = time_msg_end - time_msg_start;
    }
    time_tot_end = omp_get_wtime();
    cout << "Average time per message: " << (time_tot_end - time_tot_start)/(double)1e6 << "[µs]" <<endl;


    // Printing values
    //stringstream ss;
    //ss << path.substr(15,path.length()-15) << "-msg";
    //string output_file = ss.str();
    //std::ofstream file(output_file.c_str());
    //file << (time_tot_end - time_tot_start)/(double)10000 << endl;
    //file.close();
    //// END

    return 0;
}

string check_input_flags(int argc, char *argv[]){

    bool help = false;
    std::string path;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h"     , "Produce help message")
        ("data,d"     , po::value<std::string>() , "Path to the data directory")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
    }

    if (vm.count("data")) {
        path = vm["data"].as<std::string>();
        cout << "Using directory: " << path << endl;
    } else { cout << "You must set the «data directory»" << endl; cout << desc << endl;}

    if(help){
        cout << "Type «"<< argv[0] << " -h» for more details" << endl;
        cout << endl;
    }

    return path;
}
