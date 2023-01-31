export module ips.command:argument;

import <string>;

namespace ips::command {
    export class Argument {
    public:
        Argument(
            const std::string& flag,
            const std::string& name,
            const std::string& helpMessage = "",
            bool required = false
        ) :
            _flag(flag),
            _name(name),
            _helpMessage(helpMessage),
            _required(required)
        {}

        const std::string& getFlag() const {
            return _flag;
        }

        void setFlag(const std::string& flag) {
            _flag = flag;
        }

        const std::string& getHelpMessage() const {
            return _helpMessage;
        }

        void setHelpMessage(const std::string& helpMessage) {
            _helpMessage = helpMessage;
        }

        bool isRequired() const {
            return _required;
        }

        void setRequired(bool required) {
            _required = required;
        }

    private:
        std::string _flag;
        std::string _name;
        std::string _helpMessage;
        bool _required;
    };
}