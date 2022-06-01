#include <iostream>

template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

// template <size_t N>
// struct AllOdd {
//   constexpr static bool is_curr_odd = is_odd<N>;
//   constexpr static bool is_pre_odd  = AllOdd<N - 1>::value;
//   constexpr static bool value       = is_curr_odd & is_pre_odd;
// };

template <bool cur, typename TNext>
constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template <size_t N>
struct AllOdd_ {
  constexpr static bool is_curr_odd = is_odd<N>;
  constexpr static bool value       = AndValue<is_curr_odd, AllOdd_<N - 1>>;
};

template <>
struct AllOdd_<1> {
  constexpr static bool value = is_odd<1>;
};

int main() {
  std::cout << std::boolalpha;
  // std::cout << AllOdd<10>::value << std::endl;
  // std::cout << AllOdd<1>::value << std::endl;

  std::cout << AllOdd_<10>::value << std::endl;
  std::cout << AllOdd_<1>::value << std::endl;
}