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
                std::this_thread::sleep_for(std::chrono::milliseconds(this->step));
                std::lock_guard<std::mutex> lg{this->mtx};
                this->curr_time += std::chrono::seconds(1);
                printer(this->curr_time);
            }
        }

        void set_time(int hours, int minutes, int seconds){
            printer("in set time");
            std::lock_guard<std::mutex> lg{this->mtx};
            std::time_t t{std::chrono::system_clock::to_time_t(this->curr_time)};
            std::tm* ptm{std::localtime(&t)};
            ptm->tm_hour = hours;
            ptm->tm_min = minutes;
            ptm->tm_sec = seconds;
            t = std::mktime(ptm);
            this->curr_time = std::chrono::system_clock::from_time_t(t);
        }

        auto get_time(){
            std::lock_guard<std::mutex> lg{this->mtx};
            std::time_t t{std::chrono::system_clock::to_time_t(this->curr_time)};
            std::tm* ptm{std::localtime(&t)};
            return std::make_tuple(ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        }

        long to_time(){
            std::lock_guard<std::mutex> lg{this->mtx};
            std::time_t tmp = std::chrono::system_clock::to_time_t(this->curr_time);
            return static_cast<long>(tmp);

        }

        void from_time(time_t tmp){
            std::lock_guard<std::mutex> lg{this->mtx};
            this->curr_time = std::chrono::system_clock::from_time_t(tmp);
        }

    private:
        int step;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
        std::mutex mtx;
};