export module asyncpp.task:loop;

import :queue;
import <cstdint>;
import <chrono>;

namespace asyncpp::task {

export class AsyncTaskLoop {
public:
    // 常量，定义了任务循环的等待间隔时间（单位为毫秒）
    static const int32_t SLEEP_MS = 1000;

    static AsyncTaskLoop& getInstance();
    static void start() {
        getInstance().startLoop();
    }

private:
    // 支持单例模式，通过default修饰符说明构造函数使用默认版本
    AsyncTaskLoop() = default;
    // 支持单例模式，通过delete修饰符说明拷贝构造函数不可调用
    AsyncTaskLoop(const AsyncTaskLoop&) = delete;
    // 支持单例模式，通过delete修饰符说明赋值操作符不可调用
    AsyncTaskLoop& operator=(const AsyncTaskLoop&) = delete;

    void startLoop() {
        while (true) {
            loopExecution();
            std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
        }
    }

    void loopExecution() {
        AsyncTask asyncEvent;
        if (!AsyncTaskQueue::getInstance().dequeue(&asyncEvent)) {
            return;
        }

        asyncEvent.handler();
    }
};

AsyncTaskLoop& AsyncTaskLoop::getInstance() {
    static AsyncTaskLoop eventLoop;

    return eventLoop;
}

}