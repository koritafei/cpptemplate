#include <iostream>

template <typename T>
struct RemoveReferenceConst_ {
private:
  using inter_type = typename std::remove_reference<T>::type;

public:
  using type = typename std::remove_const<inter_type>::type;
};

template <typename T>
using RemoveReferenceConst = typename RemoveReferenceConst_<T>::type;

struct A;
struct B;

template <typename T>
constexpr size_t Fun = 0;

template <>
constexpr size_t Fun<A> = 1;

template <>
constexpr size_t Fun<B> = 2;

template <typename TW>
struct Wrapper {
  template <typename T, typename Dummy = void>
  struct Fun_ {
    constexpr static size_t value = 0;
  };

  template <typename Dummy>
  struct Fun_<int, Dummy> {
    constexpr static size_t value = 1;
  };
};

int main() {
  RemoveReferenceConst<const int &> h = 3;
  std::cout << h << std::endl;
}
