module;

#ifndef _WINDOWS_
#include <Windows.h>
#endif // _WINDOWS_

export module asyncpp.hp:loop;

import :task;
import asyncpp.task.queue;

import <thread>;
import <chrono>;
import <thread>;
import <functional>;

namespace asyncpp::hp {
    export class AsyncHpLoop {
    public:
        // 常量，定义了任务循环的等待间隔时间（单位为毫秒）
        static const int32_t SLEEP_MS = 100;

        static AsyncHpLoop& start();

    private:
        // 支持单例模式，将其定义为private，防止外部调用构造函数
        AsyncHpLoop() {
            _thread = std::jthread(std::bind(&AsyncHpLoop::loopMain, this));
            auto nativeWorkerHandle = _thread.native_handle();
            ::SetThreadPriority(nativeWorkerHandle, THREAD_PRIORITY_HIGHEST);
        }
        // 支持单例模式，通过delete修饰符说明拷贝构造函数不可调用
        AsyncHpLoop(const AsyncHpLoop&) = delete;
        // 支持单例模式，通过delete修饰符说明赋值操作符不可调用
        AsyncHpLoop& operator=(const AsyncHpLoop&) = delete;

        void loopExecution() {
            AsyncHpTask opItem;
            if (!AsyncHpTaskQueue::getInstance().dequeue(&opItem)) {
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

        // jthread对象，为高性能计算线程，jthread让该线程结束之前整个进程都不会结束
        std::jthread _thread;
    };

    AsyncHpLoop& AsyncHpLoop::start() {
        static AsyncHpLoop ioLoop;

        return ioLoop;
    }
}
