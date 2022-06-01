#include <iostream>

template <typename T>
struct Base {
  template <typename TI>
  void func(const TI &input) {
    T *ptr = static_cast<T *>(this);
    ptr->Imp(input);
  }

  static void Func() {
    T::IMP();
  }
};

struct Derive : public Base<Derive> {
  template <typename TI>
  void Imp(const TI &input) {
    std::cout << input << std::endl;
  }

  static void IMP() {
    std::cout << "virtual function" << std::endl;
  }
};

int main() {
  Derive d;
  d.func("derived base");

  Derive::Func();
}
