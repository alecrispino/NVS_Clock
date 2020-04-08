#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    tcp::iostream strm{"localhost", "1000"};

    if(strm){
        string data;
        getline(strm, data);
        cout << data << endl;
        strm.close();
    }else{
        cerr << "Could not connect to Server." << endl;
    }

    return EXIT_SUCCESS;
}