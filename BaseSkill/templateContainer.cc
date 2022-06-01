#include <iostream>
#include <thread>

template <int... args>
struct IntContainer;

template <bool... args>
struct BoolContainer;

template <typename... types>
struct TypesContainer;

template <template <typename> class... T>
struct TemplateCont;

template <template <typename...> class... T>
struct TemplateCont2;

int main() {
}