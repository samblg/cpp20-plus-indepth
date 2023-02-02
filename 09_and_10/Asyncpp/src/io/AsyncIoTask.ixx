export module asyncpp.io:task;

import asyncpp.core;
import asyncpp.task;
import <functional>;
import <vector>;
import <mutex>;

namespace asyncpp::io {

export struct AsyncIoTask {
    using ResumeHandler = std::function<void()>;
    using TaskHandler = std::function<void()>;

    // 协程唤醒函数
    ResumeHandler resumeHandler;
    // I/O任务函数
    TaskHandler taskHandler;
};

export class AsyncIoTaskQueue {
public:
    static AsyncIoTaskQueue& getInstance();

    void enqueue(const AsyncIoTask& item) {
        std::lock_guard<std::mutex> guard(_queueMutex);

        _queue.push_back(item);
    }

    bool dequeue(AsyncIoTask* item) {
        std::lock_guard<std::mutex> guard(_queueMutex);

        if (_queue.size() == 0) {
            return false;
        }

        *item = _queue.back();
        _queue.pop_back();

        return true;
    }

    size_t getSize() const {
        return _queue.size();
    }

private:
    // I/O任务队列
    std::vector<AsyncIoTask> _queue;
    // I/O任务队列互斥锁，用于实现线程同步，确保队列操作的线程安全
    std::mutex _queueMutex;
};

AsyncIoTaskQueue& AsyncIoTaskQueue::getInstance() {
    static AsyncIoTaskQueue queue;

    return queue;
}

}
