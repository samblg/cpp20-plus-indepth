#include "logging/Logger.h"
#include "logging/Handler.h"
#include "logging/handlers/DefaultHandler.h"
#include "logging/handlers/StreamHandler.h"
#include "logging/handlers/FileHandler.h"
#include "logging/formatters/CFormatter.h"
#include "logging/formatters/StreamFormatter.h"
#include "logging/formatters/ModernFormatter.h"
#include <iostream>
#include <memory>
#include <tuple>
#include <fstream>

int main() {
    using logging::Logger;
    using logging::LoggerFactory;
    using logging::handlers::DefaultHandler;
    using logging::handlers::StreamHandler;
    using logging::handlers::FileHandler;
    using logging::Level;

    // 创建名为Root1的Logger，日志等级为DEBUG
    auto logger1 = LoggerFactory<Level::Debug>::createLogger("Root1", std::make_tuple(
        // 创建StreamHandler，处理器等级为DEBUG，格式化器实现为C风格formatter
        StreamHandler<Level::Debug>(logging::formatters::cstr::formatRecord)
    ));
    // INFO等级高于DEBUG，输出到控制台
    logger1.info("hello");
    // TRACE等级低于DEBUG，被丢弃
    logger1.trace("world");

    // 创建名为Root2的Logger，日志等级为WARNING（默认）
    auto logger2 = LoggerFactory<>::createLogger("Root2");
    // INFO等级低于WARNING，日志会被丢弃
    logger2.info("hello");
    // ERROR等级高于WARNING，输出到控制台
    logger2.error("world");

    // 创建名为Root3的Logger，日志等级为DEBUG
    auto logger3 = LoggerFactory<Level::Debug>::createLogger("Root3", std::make_tuple(
        // 创建Handler1：DefaultHandler，处理器等级为DEBUG，格式化器实现为C++流风格formatter
        DefaultHandler<Level::Debug>(logging::formatters::stream::formatRecord),
        // 创建Handler2：DefaultHandler，处理器等级为WARNING（默认），格式化器实现为默认formatter
        DefaultHandler()
    ));
    // INFO等级高于DEBUG，低于WARNING，被Handler1输出到控制台，被Handler2丢弃
    logger3.info("hello");
    // CRITICAL等级同时高于DEBUG与WARNING，同时被Handler1与Handler2输出到控制台
    logger3.critical("world");

    // 创建名为Root4的Logger，日志等级为DEBUG
    auto logger4 = LoggerFactory<Level::Debug>::createLogger("Root4", std::make_tuple(
        // 创建StreamHandler，处理器等级为DEBUG，通过移动构造函数获取文件输出流的所有权，格式化器为基于std::format的formatter
        StreamHandler<Level::Debug>(std::ofstream("hello.log"), logging::formatters::modern::formatRecord)
    ));
    // INFO等级高于DEBUG，输出到hello.log
    logger4.info("hello, world");
    // WARNING等级高于DEBUG，输出到hello.log
    logger4.warning("world");

    // 创建名为Root5的Logger，日志等级为DEBUG
    auto logger5 = LoggerFactory<Level::Debug>::createLogger("Root5", std::make_tuple(
        // 创建FileHandler，处理器等级为DEBUG，通格式化器为默认格式化器
        FileHandler<Level::Debug>("file.log")
    ));
    // INFO等级高于DEBUG，输出到file.log
    logger5.info("hello, file");
    // INFO等级高于DEBUG，输出到file.log
    logger5.info("world");

    return 0;
}