#include <concepts>
#include <iostream>

class BaseClass {
public:
    int getValue() const {
        return 1;
    }
};

class DerivedClass: public BaseClass {
public:
    int getValue() const {
        return 2;
    }
};

class NonDerivedClass {
public:
    int getValue() const {
        return 3;
    }
};

template<class T>
concept DerivedOfBaseClass = std::is_base_of_v<BaseClass, T>;

template <DerivedOfBaseClass T>
void doGetValue(const T& a) {
    std::cout << "Get value:" << a.getValue() << std::endl;
}

int c2() {
    DerivedClass d;
    doGetValue(d);

    BaseClass b;
    doGetValue(b);

    // 解除注释会引发错误
    // NonDerivedClass n;
    // doGetValue(n);

    return 0;
}

int main() {
    c2();

    return 0;
}
