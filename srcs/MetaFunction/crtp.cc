#include <iostream>

template <typename T>
struct Base {
  template <typename TI>
  void Fun(const TI &input) {
    T *ptr = static_cast<T *>(this);
    ptr->Imp(input);
  }

  static void fun() {
    T::imp_static();
  }
};

struct Derived : public Base<Derived> {
  template <typename TI>
  void Imp(const TI &input) {
    std::cout << "imp: " << input << std::endl;
  }

  static void imp_static() {
    std::cout << "derived static func" << std::endl;
  }
};

int main() {
  Derived d;
  d.Fun("Implementation from derived class");
  Derived::fun();
}
