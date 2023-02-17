export module ips.network:server;

import <string>;
import <cstdint>;
import <functional>;
import <vector>;
import <memory>;
import <iostream>;

import :connection;

namespace ips::network {
    export using ConnectionPtr = std::shared_ptr<Connection>;
    export using OnConnectionHandler = std::function<void(ConnectionPtr)>;

    export class Server {
    public:
        Server(const std::string& host, int32_t port) :
            _host(host), _port(port) {}

        void setHost(const std::string& host) {
            _host = host;
        }

        const std::string& getHost() const {
            return _host;
        }

        void setPort(int32_t port) {
            _port = port;
        }

        int32_t getPort() const {
            return _port;
        }

        void startListen() {
            std::cout << "Start listened at " << _host << ":" << _port << std::endl;
        }

        void onConnection(OnConnectionHandler handler) {
            _handlers.push_back(handler);
        }

    private:
        std::string _host;
        int32_t _port;
        std::vector<OnConnectionHandler> _handlers;
    };
}