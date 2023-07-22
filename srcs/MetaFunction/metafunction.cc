#include <iostream>

constexpr int func(int a) {
  return a + 1;
}

static int call_count = 1;
int        func2(int a) {
  return a + (call_count++);
}

template <typename T>
struct Fun_ {
  using type = T;
};

template <>
struct Fun_<int> {
  using type = unsigned int;
};

template <>
struct Fun_<long> {
  using type = unsigned long;
};

template <typename T>
using Fun = typename Fun_<T>::type;

int main() {
  std::cout << func(2) << std::endl;
  std::cout << func2(2) << std::endl;
  std::cout << func2(2) << std::endl;

  Fun_<int>::type h = 10;
  std::cout << h << std::endl;
}
