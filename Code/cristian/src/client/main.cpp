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
    Clock clock(1800);
    thread thread{ref(clock)};
    thread.detach();
    clock.set_time(12,2,10);

    //Cristian
    long t0;
    long t1;
    long I;
    long ts;

    long new_tp;

    int counter{0};

    while(counter != 3){

        tcp::iostream strm{"localhost", to_string(port)};

        if(strm){
            string data;
            strm << name << endl;
            t0 = clock.to_time();
            printer("t0: " + to_string(t0));
            spdlog::info("client sent message");

            if(strm >> I){//wenn antwort gekommen
                t1 = clock.to_time();//antwortzeitpunkt
                strm >> ts;
                printer("t1: " + to_string(t1) + " " + to_string(I) + " ts:" + to_string(ts));

                new_tp = ts + ((t1-t0-I)/2);

                spdlog::info("Setting client time");
                clock.from_time(new_tp);
                spdlog::info("Client time set");
            }
            strm.close();
        }else{
            spdlog::error("Could not connect to Server.");
        }

        this_thread::sleep_for(chrono::seconds(10));
        counter++;
    }

    spdlog::info("Client finished.");

    return EXIT_SUCCESS;
}