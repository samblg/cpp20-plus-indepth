export module ips.network:response;

import <string>;
import <iostream>;

namespace ips::network{
    export class Response {
    public:
        Response() {}

        void send(const std::string& data) {
            std::cout << "Sent data" << data.size() << std::endl;
        }
    };
}