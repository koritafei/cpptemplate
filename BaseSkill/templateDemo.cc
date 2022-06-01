#include <iostream>

template <typename TW>
struct Wrapper {
  template <typename T, typename TDummy = void>
  struct Fun_ {
    constexpr static size_t value = 0;
  };

  template <typename TDummy>
  struct Fun_<int, TDummy> {
    constexpr static size_t value = 1;
  };
};

int main() {
  constexpr size_t h = Wrapper<int>::Fun_<int>::value;
  std::cout << h << std::endl;
}