#include <iostream>

template <template <typename> typename T1, typename T2>
struct Fun_ {
  using type = typename T1<T2>::type;
};

template <template <typename> typename T1, typename T2>
using Fun = typename Fun_<T1, T2>::type;

template <bool AddOrRemoveRef>
struct func_;

template <>
struct func_<true> {
  template <typename T>
  using type = std::add_lvalue_reference<T>;
};

template <>
struct func_<false> {
  template <typename T>
  using type = std::remove_reference<T>;
};

template <typename T>
using Rev_ = typename func_<false>::template type<T>;

template <typename T>
using Res_ = typename func_<true>::template type<T>;

int main() {
  Fun<std::remove_reference, int &> h = 2;
  std::cout << h << "\t" << typeid(h).name() << std::endl;
  Rev_<int &>::type t = 5;
  std::cout << t << "\t" << typeid(t).name() << std::endl;
  Res_<int>::type s = t;
  std::cout << s << "\t" << typeid(s).name() << std::endl;
}
