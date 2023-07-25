#include <iostream>
#include <tuple>
#include <type_traits>

template <typename TArray>
struct Size_;

template <template <typename...> class Cont, typename... T>
struct Size_<Cont<T...>> {
  constexpr static size_t value = sizeof...(T);
};

template <typename T>
using RemConstRef = std::remove_cv_t<std::remove_reference_t<T>>;

template <typename TArray>
constexpr static size_t Size = Size_<RemConstRef<TArray>>::value;

template <typename TSeqCont>
struct Head_;

template <template <typename...> class Container,
          typename TH,
          typename... TCases>
struct Head_<Container<TH, TCases...>> {
  using type = TH;
};

template <typename TSeqCont>
struct Tail_;
template <template <typename...> class Container,
          typename TH,
          typename... TCases>
struct Tail_<Container<TH, TCases...>> {
  using type = Container<TCases...>;
};

template <typename T, size_t ID>
struct At_;

template <template <typename...> class TCont,
          typename TCurType,
          typename... TTypes,
          size_t ID>
struct At_<TCont<TCurType, TTypes...>, ID> {
  using type = typename At_<TCont<TTypes...>, ID - 1>::type;
};

template <template <typename...> class TCont,
          typename TCurrtype,
          typename... TTypes>
struct At_<TCont<TCurrtype, TTypes...>, 0> {
  using type = TCurrtype;
};

/// tranform
template <typename TInCont,
          template <typename>
          typename F,
          template <typename...>
          typename TOutCont>
struct Transform_;

template <template <typename...> typename TInCont,
          typename... TInputs,
          template <typename>
          typename F,
          template <typename...>
          typename TOutCont>
struct Transform_<TInCont<TInputs...>, F, TOutCont> {
  using type = TOutCont<typename F<TInputs>::type...>;
};

template <typename TInCont,
          template <typename>
          typename F,
          template <typename...>
          typename TOutCont>
using Transform = typename Transform_<TInCont, F, TOutCont>::type;

// template <typename TFisrstSet, typename TSecondSet>
// struct IsEqual_;

// template <template <typename...> class Cont1,
//           template <typename...>
//           class Cont2,
//           typename... Params1,
//           typename... Params2>
// struct IsEqual_<Cont1<Params1...>, Cont2<Params2...>> {
//   constexpr static bool value1 = (HasKey<Cont1<Params1...>, Params2> && ...);
//   constexpr static bool value2 = (HasKey<Cont2<Params2...>, Params1> && ...);
//   constexpr static bool value  = value1 && value2;
// };

// template <typename TFirstSet, typename TSecondSet>
// constexpr bool IsEqual = IsEqual_<TFirstSet, TSecondSet>::value;

template <typename TState,
          template <typename, typename>
          typename F,
          typename... Remain>
struct imp_ {
  using type = TState;
};

template <typename TState,
          template <typename, typename>
          typename F,
          typename T0,
          typename... Remain>
struct imp_<TState, F, T0, Remain...> {
  using type = typename imp_<F<TState, T0>, F, Remain...>::type;
};

template <typename TInitState,
          typename TInputCont,
          template <typename, typename>
          typename F>
struct Fold_;

template <typename TInitState,
          template <typename...>
          class TCont,
          typename... TParams,
          template <typename, typename>
          typename F>
struct Fold_<TInitState, TCont<TParams...>, F> {
  template <typename S, typename I>
  using FF = typename F<S, I>::type;

  using type = typename imp_<TInitState, FF, TParams...>::type;
};

template <typename TInitState,
          typename TInputCont,
          template <typename, typename>
          typename F>
using Fold = typename Fold_<TInitState, TInputCont, F>::type;

int main() {
  using Cont            = std::tuple<char, double, int>;
  constexpr size_t Res1 = Size<Cont>;
  constexpr size_t Res2 = Size<Cont&>;

  std::cout << Res1 << "\t" << Res2 << std::endl;
}