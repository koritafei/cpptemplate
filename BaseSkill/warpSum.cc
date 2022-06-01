#include <iostream>

// template <size_t A>
// struct Warp {
//   template <size_t ID, typename TDummy = void>
//   struct imp {
//     constexpr static size_t value = ID + imp<(ID - 1)>::value;
//   };

//   template <size_t ID>
//   constexpr static size_t value = imp<ID + A>::value;
// };

template <size_t ID>
struct imp {
  constexpr static size_t value = ID + imp<ID - 1>::value;
};

template <>
struct imp<0> {
  constexpr static size_t value = 0;
};

template <size_t A>
struct Warp {
  template <size_t Id>
  constexpr static size_t value = imp<Id + A>::value;
};

int main() {
  std::cerr << Warp<3>::value<2> << std::endl;
  std::cerr << Warp<100>::value<10> << std::endl;
}
