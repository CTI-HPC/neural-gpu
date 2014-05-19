#include "TestUtils.hpp"

void parse_info_file(string path, int &N, int &H, int &M){

    path += string("info.txt");
    string line,sub;
    int count_line=0;
    ifstream source(path.c_str());
    if(source.is_open()){
        while(source.good()){
            getline(source,line);
            istringstream iss(line);
            iss >> sub;
            if (count_line == 3){
                N = atoi(sub.c_str());
            }
            else if (count_line == 4){
                H = atoi(sub.c_str());
            }
            else if (count_line == 5){
                M = atoi(sub.c_str());
            }
            count_line++;
        }
        source.close();
    }
}

bool check_flags(int argc, char *argv[], string &path, int &method, int &activation, int &iter, int &th){

    string str_method;
    string str_act;
    string methods[2] = {"gpu","cpu"};
    string options[2] = {"no","yes"};
    bool help = false;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h"     , "Produce help message")
        ("data,d"     , po::value<std::string>() , "Path to the data directory")
        ("prob,p"     , po::value<std::string>() , "Use an activation function on the «output» vector")
        ("method,m"   , po::value<std::string>() , "Execution method «gpu» (default) or «cpu»")
        ("iter,i"     , po::value<int>()         , "Number of iterations to obtain the execution time")
        ("threads,t"  , po::value<int>()         , "Number of threads for the GPU implementation")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << endl;
        return false;
    }

    // Mandatory flags
    //  * Data directory
    //  * Execution method
    if (vm.count("data")) {
        path = vm["data"].as<std::string>();
        cout << "Using directory: " << path << endl;
    } else { cout << "You must set the «data directory»" << endl; cout << desc << endl; return false;}


    // Optional flags
    //  * Use activation function
    //  * Execution method
    //  * Number of iterations
    //  * Number of threads
    if (vm.count("prob")) {
        str_act = vm["prob"].as<std::string>();
        if (!str_act.compare("no")){
            activation = 0;
        }
        cout << "Using probabilistic output: " << options[activation]<< endl;
    } else { cout << "Using probabilistic output: "<< options[activation] << endl; help = true;}

    if (vm.count("method")) {
        str_method = vm["method"].as<std::string>();
        if (!str_method.compare("cpu")){
            method = 1;
        }
        cout << "Using method: " << methods[method]<< endl;
    } else { cout << "Using default method: "<< methods[method] << endl; help = true;}

    if (vm.count("iter")) {
        iter = vm["iter"].as<int>();
        cout << "Using number of iterations: " << iter << endl;
    } else { cout << "Using default iteration number: "<< iter << endl; help = true;}

    if (vm.count("threads")) {
        th = vm["threads"].as<int>();
        cout << "Using number of threads: " << th << endl;
    } else { cout << "Using default number of threads: " << th << endl; help = true;}

    if(help){
        cout << "Type «"<< argv[0] << " -h» for more details" << endl;
        cout << endl;
    }


    return true;
}

void print_diff(string path, float *output, int M){

    path += string("output.txt");
    vector<float> base_output;
    ifstream source(path.c_str());
    back_insert_iterator<vector<float> > bii(base_output);
    copy(istream_iterator<float>(source),
              istream_iterator<float>(),
              bii);
    float *txt_output = &base_output[0];

    float diffs[M];
    float greater = 0;
    for (int i = 0; i < M; i++) {
        diffs[i] = fabs(output[i] - txt_output[i]);
        if (diffs[i] > greater){
            greater = diffs[i];
        }
    }
    cout << "Error considering a probabilistic output" << endl;
    cout << "Greatest error: " << greater << endl;
}

void load_matrix(std::vector<float>& matrix, std::string file_name) {
    matrix.clear();
    std::ifstream source(file_name.c_str());
    std::back_insert_iterator<std::vector<float> > bii(matrix);
    std::copy(std::istream_iterator<float>(source),
              std::istream_iterator<float>(),
              bii);
}
