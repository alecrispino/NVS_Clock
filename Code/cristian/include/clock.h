#pragma once
#include <chrono>
#include <mutex>
#include <thread>

#include "print.h"



class Clock{
    public:
        Clock(): step{1000}{ //default constructor -> step = 1s
            this->curr_time = std::chrono::system_clock::now();
        }; 

        Clock(int val):step{val}{  //step = beliebige zeit
            this->curr_time = std::chrono::system_clock::now();
        };

        void operator()(){
            while(true){
                std::lock_guard<std::mutex> lg{this->mtx};
                std::this_thread::sleep_for(std::chrono::milliseconds(this->step));
                this->curr_time += std::chrono::seconds(1);
                printer(this->curr_time);
            }
        }

    private:
        int step;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
        std::mutex mtx;
};