#include <cstdint>
#include <iostream>

extern int32_t add(int32_t a, int32_t b);

int main() {
  int32_t sum = add(1, 2);
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
