
#include <iostream>

template <bool IsFeedbackOut,
          typename T,
          std::enable_if_t<IsFeedbackOut>* = nullptr>
void FeedbackOut(T&& t) {
  std::cout << "fisrt function" << std::endl;
}

template <bool IsFeedbackOut,
          typename T,
          std::enable_if_t<!IsFeedbackOut>* = nullptr>
void FeedbackOut(T&& t) {
  std::cout << "second function" << std::endl;
}

/// 多种返回类型
// template <bool check, std::enable_if_t<check>* = nullptr>
// auto fun() {
//   return (int)0;
// }

// template <bool check, std::enable_if_t<!check>* = nullptr>
// auto fun() {
//   return (double)0;
// }

// template <bool check>
// auto wrapper() {
//   return fun<check>();
// }

template <bool check>
auto wrapper() {
  if constexpr (check) {
    return (int)0;
  } else {
    return (double)0;
  }
}

/// 循环
template <size_t Input>
constexpr size_t OnesCount = (Input % 2) + OnesCount<Input / 2>;

template <>
constexpr size_t OnesCount<0> = 0;

template <size_t... inputs>
constexpr size_t Accumulate = 0;

template <size_t CurInput, size_t... inputs>
constexpr size_t Accumulate<CurInput, inputs...> =
    CurInput + Accumulate<inputs...>;

template <size_t... values>
constexpr size_t fun() {
  return (0 + ... + values);
}

template <typename T>
void Helper(T t) {
  std::cout << t << std::endl;
}

template <typename... T>
void Fun(T... t) {
  (Helper(t), ...);
}

template <size_t... I>
struct Cont;

template <size_t... I>
using Con = Cont<(I + 1)...>;

int main() {
  FeedbackOut<true, int>(12);
  FeedbackOut<false, int>(123);
  std::cout << wrapper<true>() << "\t" << wrapper<false>() << std::endl;

  std::cout << OnesCount<45> << std::endl;
  constexpr size_t res = Accumulate<1, 2, 3, 4, 5>;
  std::cout << res << std::endl;

  constexpr size_t res1 = fun<1, 2, 3, 4, 5>();
  std::cout << res1 << std::endl;

  Fun("abd", 1, 2, 3, 4.5);

  using Res = Con<1, 2, 3, 4, 5>;

  std::cout << std::endl;
}