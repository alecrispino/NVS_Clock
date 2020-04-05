#include <iostream>
#include "asio.hpp"
#include "spdlog/spdlog.h"
#include "CLI11.hpp"

#include "clock.h"

using namespace std;

int main(){
    cout << "Cristian" << endl;
    spdlog::info("Cristian");

    Clock c{400};
    c();

    return EXIT_SUCCESS;
}