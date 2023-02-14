export module asyncpp.hp:task;

import asyncpp.core;
import <functional>;
import <vector>;
import <mutex>;

namespace asyncpp::hp {

export struct AsyncHpTask {
    using ResumeHandler = std::function<void()>;
    using TaskHandler = std::function<void()>;

    // 协程唤醒函数
    ResumeHandler resumeHandler;
    // 计算任务函数
    TaskHandler taskHandler;
};

export class AsyncHpTaskQueue {
public:
    static AsyncHpTaskQueue& getInstance();

    void enqueue(const AsyncHpTask& item) {
        std::lock_guard<std::mutex> guard(_queueMutex);

        _queue.push_back(item);
    }

    bool dequeue(AsyncHpTask* item) {
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
    // 高性能计算任务队列
    std::vector<AsyncHpTask> _queue;
    // 高性能计算任务队列互斥锁，用于实现线程同步，确保队列操作的线程安全
    std::mutex _queueMutex;
};

AsyncHpTaskQueue& AsyncHpTaskQueue::getInstance() {
    static AsyncHpTaskQueue queue;

    return queue;
}

}
