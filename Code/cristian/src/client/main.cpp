#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"
#include <thread>
#include "clock.h"

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){
    CLI::App app{"Client"};
    int port{};
    string name{};

    app.add_option("-p", port, "Port")->default_val("9999");
    auto optionName = app.add_option("-n", name, "Clientname");
    optionName->required();

    CLI11_PARSE(app, argc, argv);

    Clock clock;
    thread thread{ref(clock)};
    thread.detach();

    while(true){
        tcp::iostream strm{"localhost", to_string(port)};

        if(strm){
            string data;
            strm << name;
            spdlog::info("client sent message");
            strm.close();
        }else{
            cerr << "Could not connect to Server." << endl;
        }

        this_thread::sleep_for(chrono::seconds(2));
    }

    return EXIT_SUCCESS;
}