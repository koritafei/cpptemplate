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

int main() {
  using Cont            = std::tuple<char, double, int>;
  constexpr size_t Res1 = Size<Cont>;
  constexpr size_t Res2 = Size<Cont&>;

  std::cout << Res1 << "\t" << Res2 << std::endl;
}