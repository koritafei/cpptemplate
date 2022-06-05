#include "facilities/var_type_dict.h"

#include <cmath>
#include <iostream>
#include <set>

struct A;
struct B;
struct Weight;
struct XX;

struct FParams : public MetaNN::VarTypeDict<struct A, struct B, struct Weight> {
};

template <typename TIn>
float fun(const TIn &in) {
  auto a      = in.template Get<A>();
  auto b      = in.template Get<B>();
  auto weight = in.template Get<Weight>();

  return a * weight + b * (1 - weight);
}

int main() {
  std::cout << fun(FParams::Create().Set<A>(1.2f).Set<B>(3.4f).Set<Weight>(
                   0.1f))
            << std::endl;
}