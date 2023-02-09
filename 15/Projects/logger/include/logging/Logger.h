#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include <memory>
#include "logging/Level.h"
#include "logging/Handler.h"
#include "logging/handlers/DefaultHandler.h"

namespace logging {
    // Logger类定义
    // Level是日志记录器的日志等级
    // HandlerTypes是所有注册的日志处理器，必须满足Handler约束
    // 通过requires要求每个Logger类必须注册至少一个日志处理器
    template <Level loggerLevel, Handler... HandlerTypes>
        requires(sizeof...(HandlerTypes) > 0)
    class Logger {
    public:
        // HandlerCount：日志记录器数量，通过sizeof...获取模板参数中不定参数的数量
        static constexpr int32_t HandlerCount = sizeof...(HandlerTypes);
        // LoggerLevel：Logger的日志等级
        static constexpr Level LoggerLevel = loggerLevel;

        // 构造函数：name为日志记录器名称，attachedHandlers是需要注册到Logger对象中的日志处理器
        // 由于日志处理器也不允许拷贝只允许移动所以这里采用的是元组的移动构造函数
        Logger(const std::string& name, std::tuple<HandlerTypes...>&& attachedHandlers) :
            // 调用std::forward转发右值引用
            _name(name), _attachedHandlers(std::forward<std::tuple<HandlerTypes...>>(attachedHandlers)) {
        }

        // 不允许拷贝
        Logger(const Logger&) = delete;
        // 不允许赋值
        Logger& operator=(const Logger&) = delete;

        // 移动构造函数：允许日志记录器对象之间移动
        Logger(Logger&& rhs) :
            _name(std::move(rhs._name)), _attachedHandlers(std::move(rhs._attachedHandlers)) {
        }

        // log：通用日志输出接口
        // 需要通过模板参数指定输出的日志等级
        // 通过requires约束丢弃比日志记录器设定等级要低的日志
        // 避免运行时通过if判断
        template <Level level>
            requires (level > loggerLevel)
        Logger& log(const std::string& message) {
            return *this;
        }

        // 通过requires约束提交等级为日志记录器设定等级及以上的日志
        template <Level level>
            requires (level <= loggerLevel)
        Logger & log(const std::string& message) {
            // 构造Record对象
            Record record{
                .name = _name,
                .level = level,
                .time = std::chrono::system_clock::now(),
                .message = message,
            };

            // 调用handleLog实际处理日志输出
            handleLog<level, HandlerCount - 1>(record);

            return *this;
        }

        // handleLog：将日志记录提交给所有注册的日志处理器
        // messageLevel为提交的日志等级
        // handlerIndex为日志处理器的注册序号
        // 通过requires约束当handlerIndex > 0时会递归调用handleLog将消息同时提交给前一个日志处理器
        template <Level messageLevel, int32_t handlerIndex>
            requires (handlerIndex > 0)
        void handleLog(const Record& record) {
            // 递归调用handleLog将消息同时提交给前一个日志处理器
            handleLog<messageLevel, handlerIndex - 1>(record);

            // 获取当前日志处理器并提交消息
            auto& handler = std::get<handlerIndex>(_attachedHandlers);
            handler.emit<messageLevel>(record);
        }

        template <Level messageLevel, int32_t handlerIndex>
            requires (handlerIndex == 0)
        void handleLog(const Record& record) {
            // 获取当前日志处理器并提交消息
            auto& handler = std::get<handlerIndex>(_attachedHandlers);
            handler.emit<messageLevel>(record);
        }

        // 提交严重错误信息（log的包装）
        Logger& critical(const std::string& message) {
            return log<Level::Critical>(message);
        }

        // 提交一般错误信息（log的包装）
        Logger& error(const std::string& message) {
            return log<Level::Error>(message);
        }

        // 提交警告信息（log的包装）
        Logger& warning(const std::string& message) {
            return log<Level::Warning>(message);
        }

        // 提交普通信息（log的包装）
        Logger& info(const std::string& message) {
            return log<Level::Info>(message);
        }

        // 提交调试信息（log的包装）
        Logger& debug(const std::string& message) {
            return log<Level::Debug>(message);
        }

        // 提交程序跟踪信息（log的包装）
        Logger& trace(const std::string& message) {
            return log<Level::Trace>(message);
        }

    private:
        // 日志记录器名称
        std::string _name;
        // 注册的日志处理器，由于日志处理器的类型与数量不定，因此这里使用元组而非数组
        std::tuple<HandlerTypes...> _attachedHandlers;
    };

    // 日志记录器生成工厂
    template <Level level = Level::Warning>
    class LoggerFactory {
    public:
        // 创建日志记录器，指定名称与处理器
        template <Handler... HandlerTypes>
        static Logger<level, HandlerTypes...> createLogger(const std::string& name, std::tuple<HandlerTypes...>&& attachedHandlers) {
            return Logger<level, HandlerTypes...>(name, std::forward<std::tuple<HandlerTypes...>>(attachedHandlers));
        }

        // 创建日志记录器，指定名称，处理器采用默认处理器（DefaultHandler）
        template <Handler... HandlerTypes>
        static Logger<level, handlers::DefaultHandler<level>> createLogger(const std::string& name) {
            return Logger<level, handlers::DefaultHandler<level>>(name, std::make_tuple(handlers::DefaultHandler<level>()));
        }
    };
}