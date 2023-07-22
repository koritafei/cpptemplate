#include <iostream>

template <typename T>
struct Identity_ {
  using type = T;
};

template <typename TBooleanCont, typename TFunCont>
struct CompilerTimeSwitch_;

template <bool curBool,
          bool... TBools,
          template <typename...>
          class TFunCont,
          typename curFun,
          typename... TFuncs>
struct CompilerTimeSwitch_<std::integer_sequence<bool, curBool, TBools...>,
                           TFunCont<curFun, TFuncs...>> {
  static_assert(sizeof...(TBools) == sizeof...(TFuncs) ||
                sizeof...(TBools) + 1 == sizeof...(TFuncs));
  using type = typename std::conditional_t<
      curBool,
      Identity_<curFun>,
      CompilerTimeSwitch_<std::integer_sequence<bool, TBools...>,
                          TFunCont<TFuncs...>>>::type;
};

template <template <typename...> class TFunCont, typename currFunc>
struct CompilerTimeSwitch_<std::integer_sequence<bool>, TFunCont<currFunc>> {
  using type = currFunc;
};

template <typename TBooleanCont, typename TFunCont>
using CompilerTimeSwitch =
    typename CompilerTimeSwitch_<TBooleanCont, TFunCont>::type;

/// 判断从0~N的每个数是否都为奇数
template <size_t N>
constexpr bool is_odd = ((N % 2) == 1);

template <bool cur, typename TNext>
constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template <size_t N>
struct AllOdd_ {
  constexpr static bool is_cur_odd = is_odd<N>;
  constexpr static bool value      = AndValue<is_cur_odd, AllOdd_<N - 1>>;
};

template <>
struct AllOdd_<0> {
  const static bool value = is_odd<0>;
};

int main() {
  std::cout << AllOdd_<5>::value << std::endl;
}
