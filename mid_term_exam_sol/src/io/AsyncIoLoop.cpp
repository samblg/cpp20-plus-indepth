export module asyncpp.io:loop;

import :task;
import asyncpp.task;

import <thread>;
import <chrono>;
import <functional>;

namespace asyncpp::io {
    export class AsyncIoLoop {
    public:
        // 常量，定义了任务循环的等待间隔时间（单位为毫秒）
        static const int32_t SLEEP_MS = 1000;

        static AsyncIoLoop& start();

    private:
        // 支持单例模式，将其定义未private，防止外部调用构造函数
        AsyncIoLoop() {
            _thread = std::jthread(std::bind(&AsyncIoLoop::loopMain, this));
        }
        // 支持单例模式，通过delete修饰符说明拷贝构造函数不可调用
        AsyncIoLoop(const AsyncIoLoop&) = delete;
        // 支持单例模式，通过delete修饰符说明赋值操作符不可调用
        AsyncIoLoop& operator=(const AsyncIoLoop&) = delete;

        void loopExecution() {
            AsyncIoTask opItem;
            if (!AsyncIoTaskQueue::getInstance().dequeue(&opItem)) {
                return;
            }

            opItem.taskHandler();

            auto& asyncEventQueue = asyncpp::task::AsyncTaskQueue::getInstance();
            asyncEventQueue.enqueue({
                .handler = opItem.resumeHandler
            });
        }

        void loopMain() {
            while (true) {
                loopExecution();
                std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MS));
            }
        }
        
        // jthread对象，为I/O线程，jthread让该线程结束之前整个进程都不会结束
        std::jthread _thread;
    };

    AsyncIoLoop& AsyncIoLoop::start() {
        static AsyncIoLoop ioLoop;

        return ioLoop;
    }
}
