#include <cstdint>
#include <iostream>
#include "b.h"

int main() {
  int32_t sum = add(1, 2);
  std::cout << "sum: " << sum << std::endl;

  return 0;
}
