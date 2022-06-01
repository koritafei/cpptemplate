#include <iostream>
#include <type_traits>

template <bool Check, std::enable_if_t<Check, bool> = true>
auto func() {
  return (int)0;
}

template <bool Check, std::enable_if_t<!Check, bool> = true>
auto func() {
  return (double)0;
}

template <bool Check>
auto wrapper() {
  return func<Check>();
}

// C++17
template <bool Check>
auto fun() {
  if constexpr (Check) {
    return (int)0;
  } else {
    return (double)0;
  }
}

int main() {
  std::cout << wrapper<true>() << std::endl;
  std::cout << wrapper<false>() << std::endl;

  std::cout << fun<true>() << std::endl;
  std::cout << fun<false>() << std::endl;
}