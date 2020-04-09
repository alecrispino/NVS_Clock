#include <iostream>
#include "spdlog/spdlog.h"
#include "asio.hpp"
#include "CLI11.hpp"
#include "clock.h"

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){
    CLI::App app{"Server"};
    int port{};
    app.add_option("-p", port, "Port")->default_val("9999");

    CLI11_PARSE(app, argc, argv);

    Clock clock;
    thread thread{ref(clock)};
    thread.detach();

    spdlog::info("server started");

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), static_cast<unsigned short>(port)};
    tcp::acceptor acceptor{ctx, ep};
    acceptor.listen();
    spdlog::info("server listens on port: {0:d}", port);

    string data;

    while(true){
        tcp::socket sock{ctx};
        acceptor.accept(sock);
        tcp::iostream strm{std::move(sock)};

        //getline(strm, data);
        
        if(strm >> data){//wenn afrage bekommen
            spdlog::info("client: {0}", data);
            this_thread::sleep_for(chrono::seconds(2));//wartezeit später random
            strm << 2 << endl;//wartezeit in stream schreiben
        }
    }

    return EXIT_SUCCESS;
}