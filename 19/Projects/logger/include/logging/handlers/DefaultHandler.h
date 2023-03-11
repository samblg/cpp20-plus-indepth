#pragma once

#include "logging/Handler.h"
#include <syncstream>

namespace logging::handlers {
    // 默认日志处理器
    template <Level HandlerLevel = Level::Warning>
    // 继承BaseHandler
    class DefaultHandler : public BaseHandler<HandlerLevel> {
    public:
        // 构造函数，需要指定格式化器，默认格式化器为defaultFormatter
        DefaultHandler(Formatter formatter = defaultFormatter) : BaseHandler<HandlerLevel>(formatter) {}
        // 禁止拷贝构造函数
        DefaultHandler(const DefaultHandler&) = delete;
        // 定义移动构造函数
        DefaultHandler(const DefaultHandler&& rhs) noexcept : BaseHandler<HandlerLevel>(rhs.getForamtter()) {}

        // emit用于提交日志记录
        // emitLevel > HandlerLevel的日志会被丢弃
        template <Level emitLevel>
            requires (emitLevel > HandlerLevel)
        void emit(const Record& record) {
        }

        // emitLevel <= HandlerLevel的日志会被输出到标准输出流中
        template <Level emitLevel>
            requires (emitLevel <= HandlerLevel)
        void emit(const Record& record) {
            // 调用format将日志记录对象格式化成文本字符串
            std::osyncstream(std::cout) << this->format(record) << std::endl;
        }
    };
}