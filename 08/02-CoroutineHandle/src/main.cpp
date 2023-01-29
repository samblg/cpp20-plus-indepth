#include <coroutine>
#include <exception>

template<class Promise>
struct coroutine_handle {
  constexpr coroutine_handle() noexcept;
  constexpr coroutine_handle(nullptr_t) noexcept;
  static coroutine_handle from_promise(Promise&);
  coroutine_handle& operator=(nullptr_t) noexcept;

  constexpr void* address() const noexcept;
  static constexpr coroutine_handle from_address(void* addr);

  constexpr operator coroutine_handle<void>() const noexcept;

  constexpr explicit operator bool() const noexcept;
  bool done() const;

  void operator()() const;
  void resume() const; 
  void destroy() const;

  Promise& promise() const;

private:
  void* ptr;  // exposition only
};

template<>
struct coroutine_handle<void> {
  constexpr coroutine_handle() noexcept;
  constexpr coroutine_handle(nullptr_t) noexcept;
  coroutine_handle& operator=(nullptr_t) noexcept;

  constexpr void* address() const noexcept;
  static constexpr coroutine_handle from_address(void* addr);

  constexpr explicit operator bool() const noexcept;
  bool done() const;

  void operator()() const;
  void resume() const;
  void destroy() const;

private:
  void* ptr;  // exposition only
};

int main() {
  return 0;
}
