#pragma once

#include <mutex>
#include "spdlog/spdlog.h"

std::mutex mtx;

inline std::ostream& operator<<(std::ostream& out, decltype(std::chrono::system_clock::now()) time) {
    std::time_t t{std::chrono::system_clock::to_time_t(time)};
    out << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return out;
}

void printer(std::chrono::system_clock::time_point time){
    //std::time_t t{std::chrono::system_clock::to_time_t(time)};
    std::lock_guard<std::mutex> lg{mtx};
    std::cout << time << std::endl;
}

void printer(std::string msg){
    std::lock_guard<std::mutex> ul{mtx};
    std::cout << msg << std::endl;
}

