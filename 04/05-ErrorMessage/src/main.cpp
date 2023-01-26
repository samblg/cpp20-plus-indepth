#include <vector>
#include <cstdint>
 
class TestClass {
public:
  TestClass(const TestClass&) = delete;
 
  int32_t getValue2() const {
    return 0;
  }
};
 
void c10() {
  std::vector<TestClass> v(10);
  v[0] = v[1];
}
 
int main() {
    c10();
 
    return 0;
}
