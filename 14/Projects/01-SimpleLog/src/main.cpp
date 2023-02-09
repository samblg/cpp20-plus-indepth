#include <iostream>
#include <format>
#include <string>
#include <cstdint>
#include <chrono>

// 使用 std::chrono 来打印日志的时间
using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

struct HttpLogParams {
    std::string user;
    TimePoint requestTime; // C++20 提供了chrono对format的支持
    std::string level;
    std::string ip;
    std::string method;
    std::string path;
    std::string httpVersion;
    int32_t statusCode;
    int32_t bodySize;
    std::string refer;
    std::string agent;
};

void formatOutputParams(const HttpLogParams& params);

int main() {
    HttpLogParams logParams = {
        .user = "www",
        .requestTime = std::chrono::system_clock::now(),
        .level = "INFO",
        .ip = "127.0.0.1",
        .method = "GET",
        .path = "/api/v1/info",
        .httpVersion = "HTTP/1.0",
        .statusCode = 200,
        .bodySize = 6934,
        .refer = "http://127.0.0.1/index.hmtl",
        .agent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:108.0) Gecko/20100101 Firefox/108.0",
    };

    formatOutputParams(logParams);

    return 0;
}

void formatOutputParams(const HttpLogParams& params) {
    std::string logLine = std::format("{0:<16}|{1:%Y-%m-%d}T{1:%H:%M:%OS}Z {2} {3} - \"{4} {5} {6}\" {7} {8} \"{9}\" \"{10}\"",
        params.user,
        params.requestTime,
        params.level,
        params.ip,
        params.method,
        params.path,
        params.httpVersion,
        params.statusCode,
        params.bodySize,
        params.refer,
        params.agent
    );

    std::cout << logLine << std::endl;
}