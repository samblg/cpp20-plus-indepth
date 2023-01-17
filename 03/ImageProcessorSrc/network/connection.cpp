export module ips.network:connection;

import <functional>;
import <memory>;
import <vector>;

import :request;
import :response;

namespace ips::network {
    export using RequestPtr = std::shared_ptr<Request>;
    export using ResponsePtr = std::shared_ptr<Response>;

    export using OnRequestHandler = std::function<void(RequestPtr, ResponsePtr)>;

    export class Connection {
    public:
        Connection() {}

        void onRequest(OnRequestHandler requestHandler) {
            _requestHandlers.push_back(requestHandler);
        }

    private:
        std::vector<OnRequestHandler> _requestHandlers;
    };
}