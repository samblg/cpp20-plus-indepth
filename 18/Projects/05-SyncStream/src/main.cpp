#include <iostream>
#include <string>
#include <syncstream>
#include <thread>
#include <vector>
#include <cstdint>

namespace chrono = std::chrono;

// 普通stream版本
void coutPrinter(const std::string message1, const std::string message2);
// syncstream版本
void syncStreamPrinter(const std::string message1, const std::string message2);

int main() {
    std::cout << "Cout workers:" << std::endl;
    // 创建多个thread
    std::vector<std::thread> coutWorkers;
    for (int32_t workerIndex = 0; workerIndex < 10; ++workerIndex) {
        std::thread coutWorker(coutPrinter,
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            "abcdefghijklmnopqrstuvwxyz"
        );
        coutWorkers.push_back(std::move(coutWorker));
    }
    
    // 普通thread需要手动join
    for (auto& worker : coutWorkers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    std::cout << "SyncStream workers:" << std::endl;
    // 创建多个jthread，会在析构时自动join
    std::vector<std::jthread> syncStreamWorkers;
    for (int32_t workerIndex = 0; workerIndex < 10; ++workerIndex) {
        std::jthread syncStreamWorker(
            syncStreamPrinter,
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            "abcdefghijklmnopqrstuvwxyz"
        );
        syncStreamWorkers.push_back(std::move(syncStreamWorker));
    }

    return 0;
}

void coutPrinter(const std::string message1, const std::string message2) {
    std::cout << message1 << " " << message2 << std::endl;
}

void syncStreamPrinter(const std::string message1, const std::string message2) {
    // 使用std::osyncstream包装输出流对象即可
    std::osyncstream(std::cout) << message1 << " " << message2 << std::endl;
}
