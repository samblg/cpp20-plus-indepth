export module asyncpp.task.queue;

import <functional>;
import <mutex>;
import <vector>;

namespace asyncpp::task {

export struct AsyncTask {
    // 异步任务处理函数类型
    using Handler = std::function<void()>;

    // 异步任务处理函数
    Handler handler;
};

export class AsyncTaskQueue {
public:
    static AsyncTaskQueue& getInstance();

    void enqueue(const AsyncTask& item) {
        std::lock_guard<std::mutex> guard(_queueMutex);

        _queue.push_back(item);
    }

    bool dequeue(AsyncTask* item) {
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
    // 支持单例模式，通过default修饰符说明构造函数使用默认版本
    AsyncTaskQueue() = default;
    // 支持单例模式，通过delete修饰符说明拷贝构造函数不可调用
    AsyncTaskQueue(const AsyncTaskQueue&) = delete;
    // 支持单例模式，通过delete修饰符说明赋值操作符不可调用
    AsyncTaskQueue& operator=(const AsyncTaskQueue&) = delete;

    // 异步任务队列
    std::vector<AsyncTask> _queue;
    // 异步任务队列互斥锁，用于实现线程同步，确保队列操作的线程安全
    std::mutex _queueMutex;
};

AsyncTaskQueue& AsyncTaskQueue::getInstance() {
    static AsyncTaskQueue queue;

    return queue;
}

}
