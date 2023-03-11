#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>
#include <string>
#include <Windows.h>

void simpleSleep() {
    using namespace std::literals::chrono_literals;

    std::cout << "[SIMPLE] Before simple sleep" << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "[SIMPLE] After simple sleep" << std::endl;
}

int main() {
    std::cout << "[MAIN] Before create simple thread" << std::endl;
    std::thread simpleWorker(simpleSleep);
    // 获取native handle
    auto nativeWorkerHandle = simpleWorker.native_handle();
    // 设置线程优先级
    std::cout << "THREAD_PRIORITY_HIGHEST: " << THREAD_PRIORITY_HIGHEST << std::endl;
    ::SetThreadPriority(nativeWorkerHandle, THREAD_PRIORITY_HIGHEST);
    std::cout << "Thread Priority: " << ::GetThreadPriority(nativeWorkerHandle) << std::endl;

    simpleWorker.join();

    std::cout << "[MAIN] Main function exited" << std::endl;

    return 0;
}
