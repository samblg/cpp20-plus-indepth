export module asyncpp.task:coroutine;

import <coroutine>;
import <functional>;

namespace asyncpp::task {
    // 协程类
    export struct Coroutine
    {
        // 协程Promise定义
        struct promise_type
        {
            //std::function<void()> _doneHook;
            //bool _doneHookExecuted = false;

            Coroutine get_return_object() { 
                return {
                    ._handle = std::coroutine_handle<promise_type>::from_promise(*this) 
                }; 
            }
            std::suspend_never initial_suspend() { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {}
        };

        // 协程的句柄，可用于构建Coroutine类，并在业务代码中调用接口进行相关操作
        std::coroutine_handle<promise_type> _handle;
    };

    // AsyncTaskSuspender类型声明
    export template <typename ResultType>
    struct Awaitable;
    export using AsyncTaskResumer = std::function<void()>;
    export using CoroutineHandle = std::coroutine_handle<Coroutine::promise_type>;
    export template <typename ResultType>
    using AsyncTaskSuspender = std::function<void(
        Awaitable<ResultType>*, AsyncTaskResumer, CoroutineHandle&
    )>;

    // Awaitable类型定义（当任务函数返回类型不为void时）
    export template <typename ResultType>
    struct Awaitable
    {
        // co_await时需要执行的任务，开发者可以在suspend实现中调用该函数执行用户期望的任务
        std::function<ResultType()> _taskHandler;
        // 存储任务执行的结果，会在await_resume中作为co_await表达式的值返回。
        ResultType _taskResult;
        // 存储开发者自定义的await_suspend实现，会在await_suspend中调用
        AsyncTaskSuspender<ResultType> _suspender;

        bool await_ready() { return false; }
        void await_suspend(CoroutineHandle h)
        {
            _suspender(this, [h] { h.resume(); }, h);
        }

        ResultType await_resume() {
            return _taskResult;
        }
    };

    // Awaitable类型定义（当任务函数返回类型为void时）
    export template <>
    struct Awaitable<void>
    {
        // co_await时需要执行的任务，开发者可以在suspend实现中调用该函数执行用户期望的任务
        std::function<void()> _taskHandler;
        // 存储开发者自定义的await_suspend实现，会在await_suspend中调用
        AsyncTaskSuspender<void> _suspender;

        bool await_ready() { return false; }
        void await_suspend(CoroutineHandle h)
        {
            _suspender(this, [h] { h.resume(); }, h);
        }

        void await_resume() {}
    };
}
