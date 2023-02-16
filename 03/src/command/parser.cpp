export module ips.command:parser;

import <string>;
import <map>;
import <vector>;
import <functional>;

import :argument;

namespace ips::command {
    export class Parser {
    public:
        Parser& addArgument(const Argument& argument) {
            _arguments.push_back(argument);

            return *this;
        }

        std::map<std::string, std::string> parseArgs() {
            return _parsedArgs;
        }

        std::string getNamedArgument(const std::string& name) {
            std::string value = _parsedArgs[name];

            value;
        }

        template <class T>
        T getNamedArgument(const std::string& name, std::function<T(const std::string&)> converter) {
            std::string value = _parsedArgs[name];

            return converter(value);
        }
        
    private:
        std::vector<Argument> _arguments;
        std::map<std::string, std::string> _parsedArgs;
    };
}
