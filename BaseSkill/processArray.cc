#include <iostream>

template <size_t... inputs>
constexpr size_t Accumulate = 0;

template <size_t CurrInput, size_t... inputs>
constexpr size_t Accumulate<CurrInput, inputs...> =
    CurrInput + Accumulate<inputs...>;

constexpr size_t res = Accumulate<1, 2, 3, 4, 5>;

// c++17
template <size_t... values>
constexpr size_t fun() {
  return (0 + ... + values);
}

int main() {
  std::cout << res << std::endl;

  size_t res1 = Accumulate<1, 2, 3, 4, 5>;
  std::cout << res1 << std::endl;

  constexpr size_t res2 = fun<1, 2, 3, 4, 5>();
  std::cout << res2 << std::endl;

  constexpr size_t res3 = fun<1, 2, 3, 4, 5>();
  std::cout << res3 << std::endl;
}