export module asyncpp.io:asyncify;

import <coroutine>;
import <type_traits>;
import asyncpp.core;
import asyncpp.task;
import :task;

namespace asyncpp::io {
    using asyncpp::core::Invocable;
    using asyncpp::task::Awaitable;
    using asyncpp::task::AsyncTaskResumer;
    using asyncpp::task::asyncify;
    using asyncpp::task::AsyncTaskSuspender;
    using asyncpp::task::CoroutineHandle;

    // 异步I/O任务的AsyncTaskSuspender（当任务函数返回类型不为void时）
    template <typename ResultType>
    void ioAsyncAwaitableSuspend(
        Awaitable<ResultType>* awaitable,
        AsyncTaskResumer resumer,
        CoroutineHandle& h
    ) {
        asyncpp::io::AsyncIoTask operationItem{
            .resumeHandler = [h] {
                h.resume();
            },
            .taskHandler = [awaitable]() {
                awaitable->_taskResult = awaitable->_taskHandler();
            }
        };

        asyncpp::io::AsyncIoTaskQueue::getInstance().enqueue(operationItem);
    }

    // 异步I/O任务的AsyncTaskSuspender（当任务函数返回类型为void时）
    template <>
    void ioAsyncAwaitableSuspend<void>(
        Awaitable<void>* awaitable,
        AsyncTaskResumer resumer,
        CoroutineHandle& h
    ) {
        asyncpp::io::AsyncIoTask operationItem{
            .resumeHandler = [h] {
                h.resume();
            },
            .taskHandler = [awaitable]() {
                awaitable->_taskHandler();
            }
        };

        asyncpp::io::AsyncIoTaskQueue::getInstance().enqueue(operationItem);
    }

    // 异步化工具函数，支持将普通函数f作为I/O任务异步化
    export template <Invocable T>
    auto ioAsyncify(T taskHandler) {
        using ResultType = std::invoke_result_t<T>;

        AsyncTaskSuspender<ResultType> suspender = ioAsyncAwaitableSuspend<ResultType>;
        return asyncify(taskHandler, suspender);
    }
}