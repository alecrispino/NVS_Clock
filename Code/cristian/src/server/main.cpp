#include <iostream>
#include "spdlog/spdlog.h"
#include "asio.hpp"

using namespace std;
using namespace asio::ip;

int main([[maybe_unused]]int argc, [[maybe_unused]]char* argv[]){

    int port{1000};

    spdlog::info("server started");

    asio::io_context ctx;
    tcp::endpoint ep{tcp::v4(), static_cast<unsigned short>(port)};
    tcp::acceptor acceptor{ctx, ep};
    acceptor.listen();
    spdlog::info("server listens on port: {0:d}", port);

    while(true){
        tcp::socket sock{ctx};
        acceptor.accept(sock);
        spdlog::info("client connected");
        tcp::iostream strm{std::move(sock)};

        string data;
        spdlog::info("sending data");
        strm << "server message";
        spdlog::info("data sent");
    }

    return EXIT_SUCCESS;
}