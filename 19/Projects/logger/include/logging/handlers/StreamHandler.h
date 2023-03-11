#pragma once

#include "logging/Handler.h"
#include <iostream>
#include <syncstream>

namespace logging::handlers {
    // 流日志处理器
    template <Level HandlerLevel = Level::Warning>
    class StreamHandler : public BaseHandler<HandlerLevel> {
    public:
        // 构造函数，支持通过输出流引用构建日志处理器
        StreamHandler(std::ostream& os = std::cout, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter), _ownedStream(nullptr), _stream(os) {
        }

        // 构造函数，支持调用输出流对象的移动构造函数获取输出流对象的所有权
        template <class OutputStreamType>
            requires std::is_base_of_v<std::ostream, OutputStreamType>
        StreamHandler(OutputStreamType&& ownedOs, Formatter formatter = defaultFormatter) :
            BaseHandler<HandlerLevel>(formatter),
            _ownedStream(new OutputStreamType(std::forward<OutputStreamType>(ownedOs))),
            _stream(*_ownedStream) {
        }
        
        StreamHandler(Formatter formatter) :
            BaseHandler<HandlerLevel>(formatter), _ownedStream(nullptr), _stream(std::cout) {}

        StreamHandler(const StreamHandler&) = delete;
        StreamHandler(StreamHandler&& rhs) noexcept : 
            BaseHandler<HandlerLevel>(rhs.getForamtter()), _stream(rhs._stream), _ownedStream(rhs._ownedStream) {
            rhs._ownedStream = nullptr;
        }

        ~StreamHandler() {
            if (_ownedStream) {
                delete _ownedStream;
                _ownedStream = nullptr;
            }
        }

        template <Level emitLevel>
            requires (emitLevel <= HandlerLevel)
        void emit(const Record& record) {
            std::osyncstream(_stream) << this->format(record) << std::endl;
        }

        template <Level emitLevel>
            requires (emitLevel > HandlerLevel)
        void emit(const Record& record) {
        }

    private:
        std::ostream* _ownedStream;
        std::ostream& _stream;
    };
}