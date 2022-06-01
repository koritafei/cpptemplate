#include <cxxabi.h>
#include <stdint.h>

#include <iostream>
#include <typeinfo>

std::string getNatureName(const char *name) {
  int         status     = -1;
  char *      natureName = abi::__cxa_demangle(name, NULL, NULL, &status);
  const char *dname      = (status == 0) ? natureName : name;

  std::string ret{dname};
  free(natureName);
  return ret;
}

// 返回函数类型元函数，返回类型 T
template <typename T>
struct Func_ {
  using type = T;
};

// 特化
template <>
struct Func_<int> {
  using type = unsigned int;
};

// 特化
template <>
struct Func_<long> {
  using type = unsigned long;
};

template <typename T>
using Fun = typename Func_<T>::type;

Func_<int>::type h  = 3;
Fun<int>         hh = 10;

int main() {
  std::cout << h << std::endl;

  std::cout << getNatureName(typeid(h).name()) << std::endl;

  std::cout << hh << std::endl;

  std::cout << getNatureName(typeid(hh).name()) << std::endl;
}