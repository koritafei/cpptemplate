#include <cxxabi.h>

#include <iostream>
#include <type_traits>

std::string getNatureName(const char *name) {
  int         status     = -1;
  char *      natureName = abi::__cxa_demangle(name, NULL, NULL, &status);
  const char *dname      = (status == 0) ? natureName : name;

  std::string ret{dname};
  free(natureName);
  return ret;
}

template <bool AddOrRemoveRef>
struct Func_;

template <>
struct Func_<true> {
  template <typename T>
  using type = std::add_lvalue_reference<T>;
};

template <>
struct Func_<false> {
  template <typename T>
  using type = std::remove_reference<T>;
};

template <typename T, bool AddOrRemoveRef>
using Func = typename Func_<AddOrRemoveRef>::template type<T>;

template <typename T>
using Res_ = Func<T, false>;

template <typename T>
using Res = Func<T, true>;

Res_<int &>::type h = 3;

Res<const float>::type f = 2.3f;

int main() {
  std::cout << getNatureName(typeid(h).name()) << std::endl;
  std::cout << getNatureName(typeid(f).name()) << std::endl;
}