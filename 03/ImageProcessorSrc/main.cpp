import <iostream>;
import <string>;
import <functional>;

import ips.command;
import ips.network;
import ips.image;
import ips.app;
import ips.cache;

int main() {
    std::cout << "Image Processor" << std::endl;
    
    ips::command::Parser parser;
    parser.addArgument(ips::command::Argument("--host", "host"));
    parser.addArgument(ips::command::Argument("--port", "port"));
    parser.addArgument(ips::command::Argument("--cache", "cachePath"));
    parser.parseArgs();

    std::string cachePath = parser.getNamedArgument("cachePath");
    ips::cache::CacheLoader cacheLoader(cachePath);

    std::string host = parser.getNamedArgument("host");
    int port = parser.getNamedArgument<int32_t>("port", [](const std::string& value)-> int32_t {
        return std::stoi(value);
    });
    ips::network::Server server(host, port);

    server.onConnection([&cacheLoader](ips::network::ConnectionPtr connection) -> void {
        connection->onRequest(std::bind(
            ips::app::processRequest,
            &cacheLoader,
            std::placeholders::_1,
            std::placeholders::_2
        ));
    });

    server.startListen();

    return 0;
}