#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"
#include <thread>
#include "clock.h"
#include "print.h"

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){
    //CLI11
    CLI::App app{"Client"};
    int port{};
    string name{};

    app.add_option("-p", port, "Port")->default_val("9999");
    auto optionName = app.add_option("-n", name, "Clientname");
    optionName->required();

    CLI11_PARSE(app, argc, argv);

    //Clock
    Clock clock(1300);
    thread thread{ref(clock)};
    thread.detach();

    //Cristian
    long t0;
    long t1;
    long I;

    while(true){

        tcp::iostream strm{"localhost", to_string(port)};

        if(strm){
            string data;
            strm << name << endl;
            t0 = clock.to_time();
            printer("t0: " + to_string(t0));
            spdlog::info("client sent message");

            if(strm >> I){
                t1 = clock.to_time();
                printer("t1: " + to_string(t1) + " " + to_string(I));
            }
            strm.close();
        }else{
            cerr << "Could not connect to Server." << endl;
        }

        this_thread::sleep_for(chrono::seconds(2));
    }

    return EXIT_SUCCESS;
}