#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"
#include <thread>

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    tcp::iostream strm{"localhost", "1000"};

    if(strm){
        string data;
        while(true){
            getline(strm, data);
            cout << data << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
        //strm.close();
    }else{
        cerr << "Could not connect to Server." << endl;
    }

    return EXIT_SUCCESS;
}