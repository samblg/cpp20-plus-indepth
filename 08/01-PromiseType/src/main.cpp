#include <coroutine>
#include <exception>

template<typename T>
struct promise;

template<typename T>
struct Generator : std::coroutine_handle<promise<T>> {
  using promise_type = promise<T>;
};

template<typename T>
struct promise {
  T _value;
  std::exception_ptr _exception;

  template<typename Ty>
  promise(Ty&& lambdaObj, T value) : _value(value) {}
  promise(T value) : _value(value) {}
  promise() {}

  Generator<T> get_return_object() { return { Generator<T>::from_promise(*this) }; }
  std::suspend_always initial_suspend() noexcept { return {}; }
  std::suspend_always final_suspend() noexcept { return {}; }

  std::suspend_always yield_value(T value) {
      _value = value;
      return {};
  }

  std::suspend_always return_value(T value) {
      _value = value;
      return {};
  }
  void return_void() {}
  void unhandled_exception() { _exception = std::current_exception(); }
};

int main() {
    return 0;
}
