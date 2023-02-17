export module ips.network:request;

import <string>;
import <map>;

namespace ips::network {
    export class Request {
    public:
        Request() {}

        void setPath(const std::string& path) {
            _path = path;
        }

        const std::string& getPath() {
            return _path;
        }

        void setQuery(const std::map<std::string, std::string>& query) {
            _query = query;
        }

        const std::map<std::string, std::string>& getQuery() {
            return _query;
        }

        std::string&& getBody() {
            return "";
        }

    private:
        std::string _path;
        std::map<std::string, std::string> _query;
    };
}