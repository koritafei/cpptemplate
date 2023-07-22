#include <iostream>
#include <type_traits>

template <typename T, size_t N>
struct Fun_ {
private:
  constexpr static size_t val = N > 10 ? N / 2 : N;

public:
  using type = T[val];
};

using ResType = Fun_<int, 5>::type;

template <typename T>
struct Wrapper {
  template <size_t N>
  using method = T[N];
};

template <typename T>
struct Func_ {
  using type = Wrapper<std::remove_pointer_t<T>>;
};

template <typename T>
using Fun = typename Func_<T>::type;

int main() {
  ResType arr;
  for (int i = 0; i < 5; i++) {
    arr[i] = i;
  }

  for (auto &item : arr) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  Fun<float>::template method<5> arr1;
  for (int i = 0; i < 5; i++) {
    arr1[i] = i * 0.1;
  }

  for (auto &item : arr1) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}
