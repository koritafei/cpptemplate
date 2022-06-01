#include <iostream>

template <size_t input>
constexpr size_t onecount = (input % 2) + onecount<(input / 2)>;

template <>
constexpr size_t onecount<1> = 1;

template <>
constexpr size_t onecount<0> = 0;

constexpr size_t res = onecount<45>;

int main() {
  std::cout << res << std::endl;
}