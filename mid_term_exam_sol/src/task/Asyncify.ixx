export module asyncpp.task:asyncify;

export import asyncpp.task.queue;
export import :loop;
export import :coroutine;

import asyncpp.core;
import asyncpp.hp;

namespace asyncpp::task {
    using asyncpp::core::Invocable;

    // 默认的AsyncTaskSuspender（当任务函数返回类型不为void时）
    template <typename ResultType>
    void defaultAsyncAwaitableSuspend(
        Awaitable<ResultType>* awaitable,
        AsyncTaskResumer resumer,
        CoroutineHandle& h
    ) {
        auto& asyncTaskQueue = AsyncTaskQueue::getInstance();
        asyncTaskQueue.enqueue({
            .handler = [resumer, awaitable] {
                awaitable->_taskResult = awaitable->_taskHandler();
                resumer();
            }
        });
    }

    // 默认的AsyncTaskSuspender（当任务函数返回类型为void时）
    template <>
    void defaultAsyncAwaitableSuspend<void>(
        Awaitable<void>* awaitable,
        AsyncTaskResumer resumer,
        CoroutineHandle& h
    ) {
        auto& asyncTaskQueue = AsyncTaskQueue::getInstance();
        asyncTaskQueue.enqueue({
            .handler = [resumer, awaitable] {
                awaitable->_taskHandler();
                resumer();
            }
        });
    }

    template <typename ResultType>
    void hpAsyncAwaitableSuspend(
        Awaitable<ResultType>* awaitable,
        AsyncTaskResumer resumer,
        CoroutineHandle& h
    ) {
        asyncpp::hp::AsyncHpTask operationItem{
            .resumeHandler = [h] {
                h.resume();
            },
            .taskHandler = [awaitable]() {
                awaitable->_taskResult = awaitable->_taskHandler();
            }
        };

        asyncpp::hp::AsyncHpTaskQueue::getInstance().enqueue(operationItem);
    }

    export template <Invocable T>
    auto asyncify(
        T taskHandler,
        AsyncTaskSuspender<std::invoke_result_t<T>> suspender =
        defaultAsyncAwaitableSuspend<std::invoke_result_t<T>>
    ) {
        return Awaitable<std::invoke_result_t<T>>{
            ._taskHandler = taskHandler,
                ._suspender = suspender
        };
    }

    export template <Invocable T>
    auto asyncify(
        T taskHandler,
        bool highPriority
    ) {
        if (highPriority) {
            return Awaitable<std::invoke_result_t<T>>{
                ._taskHandler = taskHandler,
                ._suspender = hpAsyncAwaitableSuspend<std::invoke_result_t<T>>
            };
        }
        return Awaitable<std::invoke_result_t<T>>{
            ._taskHandler = taskHandler,
            ._suspender = defaultAsyncAwaitableSuspend<std::invoke_result_t<T>>
        };
    }
}

