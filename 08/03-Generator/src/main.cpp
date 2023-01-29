#include <coroutine>
#include <iostream>
#include <cstdint>

struct CountGenerator {
    struct promise_type {
        int32_t _value{ 0 };

        ~promise_type() {
            std::cout << "promise_type destructed" << std::endl;
        }
        CountGenerator get_return_object() {
            return {
              ._handle = std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        std::suspend_always yield_value(int32_t value) {
            _value = value;
            return {};
        }
        void return_void() {}
    };

    std::coroutine_handle<promise_type> _handle;
};

CountGenerator doCount() {
    for (int32_t i = 0; i < 3; ++i) {
        co_yield i;
    }
}

int main() {
    auto h = doCount()._handle;
    auto& promise = h.promise();
    while (!h.done()) {
        std::cout << "Count: " << promise._value << std::endl;
        h();
    }
    h.destroy();

    return 0;
}
