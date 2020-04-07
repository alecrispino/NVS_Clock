#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"

#include "clock.h"
#include "print.h"
#include <thread>

using namespace std;

int main(){
    cout << "Cristian" << endl;
    spdlog::info("Cristian");

    Clock c;
    Clock c1;
    thread t3{ref(c1)};
    thread t{ref(c)};
    thread t2{[&c]{
        //this_thread::sleep_for(chrono::seconds(3));
        c.set_time(12,4,2);
        printer(to_string(get<0>(c.get_time())));
        printer(to_string(c.to_time()));
    }};

    t.join();
    t2.join();
    t3.join();

    return EXIT_SUCCESS;
}