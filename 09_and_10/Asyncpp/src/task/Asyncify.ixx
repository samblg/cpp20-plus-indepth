export module asyncpp.task:asyncify;

export import :queue;
export import :loop;
export import :coroutine;

import asyncpp.core;

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

    //template <typename ResultType>
    //void defaultCoroutineAsyncAwaitableSuspend(
    //    Awaitable<ResultType>* awaitable,
    //    AsyncTaskResumer resumer,
    //    CoroutineHandle& h
    //) {
    //    Coroutine c{ ._handle = h };
    //    if (!c.hasDoneHook()) {
    //        c.registerDoneHook([resumer, awaitable]() {
    //            //awaitable->_taskResult = awaitable->_taskHandler();
    //            // TODO: Assign result from promise to _taskResult
    //            resumer();
    //        });
    //    }

    //    if (c.done()) {
    //        c.next();
    //    }

    //    auto& asyncTaskQueue = AsyncTaskQueue::getInstance();
    //    asyncTaskQueue.enqueue({
    //        .handler = [resumer, awaitable, h] {
    //            Coroutine c {._handle = h };
    //            if (!c.hasDoneHook()) {
    //                c.registerDoneHook([resumer, awaitable]() {
    //                    awaitable->_taskResult = awaitable->_taskHandler();
    //                    resumer();
    //                });
    //            }

    //            if (c.done()) {
    //                
    //            }

    //        }
    //    });
    //}

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

    // 异步化工具函数，支持将普通函数f异步化
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
}

