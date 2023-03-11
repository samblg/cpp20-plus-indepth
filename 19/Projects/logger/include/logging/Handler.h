#pragma once

#include "logging/Formatter.h"
#include "logging/Level.h"
#include "logging/Record.h"
#include <string>
#include <memory>
#include <type_traits>
#include <concepts>

namespace logging {
    // Handler Concept
    // 不强制所有Handler都继承BaseHandler，只需要满足特定的接口，因此定义Concept
    template <class HandlerType>
    concept Handler = requires (HandlerType handler, const Record & record, Level level) {
        // 要求有emit成员函数
        handler.template emit<Level::Debug>(record);
        // 要求有format函数，可以将Record对象格式化为string类型的字符串
        { handler.format(record) } -> std::same_as<std::string>;
        // 要求有移动构造函数，无拷贝构造函数
    }&& std::move_constructible<HandlerType> && !std::copy_constructible<HandlerType>;

    // BaseHandler类定义
    // HandlerLevel是日志处理器的日志等级
    // 自己实现Handler时可以继承BaseHandler然后实现emit
    template <Level HandlerLevel = Level::Warning>
    class BaseHandler {
    public:
        // 构造函数：formatter为日志处理器的格式化器
        BaseHandler(Formatter formatter) : _formatter(formatter) {}

        // 不允许拷贝
        BaseHandler(const BaseHandler&) = delete;
        // 不允许赋值
        BaseHandler& operator=(const BaseHandler&) = delete;

        // 移动构造函数：允许日志处理器对象之间移动
        BaseHandler(BaseHandler&& rhs) noexcept : _formatter(std::move(rhs._formatter)) {};

        // 析构函数，考虑到会被继承，避免析构时发生资源泄露
        virtual ~BaseHandler() {}

        // getForamtter：获取formatter
        Formatter getForamtter() const {
            return _formatter;
        }

        // setForamtter：修改formatter
        void setForamtter(Formatter formatter) {
            _formatter = formatter;
        }

        // format：调用格式化器将record转换成文本字符串
        std::string format(const Record& record) {
            return _formatter(record);
        }

    private:
        // 日志处理器的格式化器
        Formatter _formatter;
    };
}