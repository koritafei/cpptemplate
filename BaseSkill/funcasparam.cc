#include <cxxabi.h>

#include <iostream>
#include <type_traits>

std::string getNatureName(const char *name) {
  int         status     = -1;
  char *      natureName = abi::__cxa_demangle(name, NULL, NULL, &status);
  const char *dname      = (status == 0) ? natureName : name;

  std::string ret{dname};
  free(natureName);
  return ret;
}

template <template <typename> class T1, typename T2>
struct Func_ {
  using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename Func_<T1, T2>::type;

int main() {
  Fun<std::remove_reference, int &> h = 3;

  int &&j = 6;
  std::cout << h << ' ' << getNatureName(typeid(h).name()) << ' ' << j << ' '
            << getNatureName(typeid(j).name()) << std::endl;
}
