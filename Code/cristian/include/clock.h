#pragma once
#include <chrono>
#include <mutex>
#include <thread>

std::mutex out_mtx;

inline std::ostream& operator<<(std::ostream& out, decltype(std::chrono::system_clock::now()) time) {
    std::time_t t{std::chrono::system_clock::to_time_t(time)};
    out << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return out;
}

class Clock{
    public:
        Clock(): step{1000}{}; //default constructor -> step = 1s

        Clock(int val):step{val}{}; //step = beliebige zeit

        void operator()(){
            while(true){
                std::this_thread::sleep_for(std::chrono::milliseconds(this->step));
                this->curr_time += std::chrono::seconds(1);
                this->print();
            }
        }

        void print(){
            std::lock_guard<std::mutex> lg{out_mtx};
            std::cout << this->curr_time << std::endl;
        }

    private:
        int step;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
};