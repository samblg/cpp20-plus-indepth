// ============= Promise的Concept定义 ===================
// PromiseType是Promise的类型，ValueType是协程中待计算的值的类型
template<typename PromiseType, typename ValueType>
concept Promise = requires(PromiseType promise) {
  { promise.get_return_object() } -> Coroutine<PromiseType>;
  { promise.initial_suspend() } -> Awaiter;
  { promise.final_suspend() } -> Awaiter;

  requires (requires(ValueType value) { promise.return_value(value); } || { promise.return_void(); })
  { promise.unhandled_exception() };
};

// ============= Awaiter的Concept定义 ===================
// AwaitSuspendResult约束了await_suspend的返回值类型
// AwaiterType是Awaiter的类型，Promise是协程的Promise类型，下同
template <typename ResultType, typename Promise>
concept AwaitSuspendResult = std::same_as<ResultType, void> ||
  std::same_as<ResultType, bool> ||
  std::same_as<ResultType, std::coroutine_handle<Promise>>;

// Awaiter约束定义，Awaiter类型必须满足requires中的所有接口约定
template <typename AwaiterType, typename Promise>
concept Awaiter = requires(AwaiterType awaiter, std::coroutine_handle<Promise> h) {
    awaiter.await_resume();
    { awaiter.await_ready() } -> std::same_as<bool>;
    { awaiter.await_suspend(h) } -> AwaitSuspendResult<Promise>;
};

// ============= Awaitable的Concept定义 ===================
// ValidCoAwait约束用于判断对于AwaitableType是否存在正确的co_await操作符重载
// co_await可以重载为成员函数或者非成员函数，约束中都需要判断
// AwaitableType是Awaitable的类型，Promise是协程的Promise类型，下同
template <typename AwaitableType, typename Promise>
concept ValidCoAwait = requires(AwaitableType awaitable) {
    { awaitable.operator co_await() } -> Awaiter<Promise>;
} || requires(AwaitableType awaitable) {
    { operator co_await(static_cast<AwaitableType&&>(awaitable)) } -> Awaiter<Promise>;
};

// Awaitable约束定义
// Awaitable必须存在正确的co_await操作符重载，或者自身是一个Awaiter
template <typename AwaitableType, typename Promise>
concept Awaitable = ValidCoAwait<AwaitableType, Promise> ||
  Awaiter<AwaitableType, Promise>;
