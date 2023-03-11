#include <iostream>
#include <thread>
#include <chrono>
#include <cstdint>
#include <string>

void simpleSleep() {
    using namespace std::literals::chrono_literals;

    std::cout << "[SIMPLE] Before simple sleep" << std::endl;
    std::this_thread::sleep_for(2000ms);
    std::cout << "[SIMPLE] After simple sleep" << std::endl;
}

// jthread的工作函数可以通过第一个类型为stop_token的参数获取线程中断请求
void stopTokenSleep(std::stop_token stoken, std::string workerName) {
    using namespace std::literals::chrono_literals;

    std::cout << "Worker name: " << workerName << std::endl;

    while (true) {
        std::cout << "[STOP_TOKEN] Before sleep" << std::endl;
        std::this_thread::sleep_for(100ms);
        std::cout << "[STOP_TOKEN] After sleep" << std::endl;

        // 调用stop_requested可以得知是否有其他线程请求中断本线程
        if (stoken.stop_requested()) {
            std::cout << "[STOP_TOKEN] Received stop request" << std::endl;

            return;
        }
    }
}

int main() {
    // ms等自定义文字量定义在std::literals::chrono_literals名称空间中
    using namespace std::literals::chrono_literals;

    std::cout << "[MAIN] Before create simple thread" << std::endl;
    // 创建线程
    std::jthread simpleWorker(simpleSleep);
    auto nativeWorkerHandle = simpleWorker.native_handle();
    std::cout << "[MAIN] After create simple thread" << std::endl;

    std::cout << "[MAIN] Before create stop token thread" << std::endl;
    // 创建线程
    std::jthread stopTokenWorker(stopTokenSleep, "Worker1");
    // 注册request_stop成功后的回调
    std::stop_callback callback(stopTokenWorker.get_stop_token(), [] {
        std::cout << "[MAIN] Called after thread stop requested" << std::endl;
    });
    std::cout << "[MAIN] After create stop token thread" << std::endl;

    std::this_thread::sleep_for(500ms);

    std::cout << "[MAIN] Request stop" << std::endl;
    stopTokenWorker.request_stop();

    std::cout << "[MAIN] Main function exited" << std::endl;

    return 0;
}
