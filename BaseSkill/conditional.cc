#include <iostream>

struct A {};
struct B {};

// c++11
template <typename T>
struct Fun_ {
  constexpr static size_t value = 0;
};

template <>
struct Fun_<A> {
  constexpr static size_t value = 1;
};

template <>
struct Fun_<B> {
  constexpr static size_t value = 2;
};

// c++14
template <typename T>
constexpr size_t Fun = 0;

template <>
constexpr size_t Fun<A> = 1;

template <>
constexpr size_t Fun<B> = 2;

int main() {
  constexpr size_t h = Fun_<B>::value;
  std::cout << h << std::endl;

  constexpr size_t hh = Fun<A>;
  std::cout << h << std::endl;
}