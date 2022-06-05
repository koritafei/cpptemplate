#ifndef __TRAITS__H__
#define __TRAITS__H__

#include <cstddef>
#include <type_traits>

namespace MetaNN {

template <typename T>
struct Identity_ {
  using type = T;
};

// Or
template <bool cur, typename TNext>
constexpr static bool orValue = true;

template <typename TNext>
constexpr static bool orValue<false, TNext> = TNext::type;

// and
template <bool cur, typename TNext>
constexpr static bool andValue = false;

template <typename TNext>
constexpr static bool andValue<true, TNext> = TNext::type;

// array empty
template <typename InArray>
struct IsArrayEmpty_;

template <template <typename...> class Cont, typename T1, typename... T2>
struct IsArrayEmpty_<Cont<T1, T2...>> {
  constexpr static bool value = false;
};

template <template <typename...> class Cont>
struct IsArrayEmpty_<Cont<>> {
  constexpr static bool value = true;
};

template <typename TArray>
constexpr static bool IsArrayEmpty = IsArrayEmpty_<TArray>::value;

// array size
template <typename TArray>
struct ArraySize_;

template <template <typename...> class Cont, typename... T>
struct ArraySize_<Cont<T...>> {
  constexpr static int value = sizeof...(T);
};

template <typename TArray>
constexpr static int value = ArraySize_<TArray>::value;

template <typename TSeqCont>
struct SeqHead_;

template <template <typename...> class Contianer,
          typename TH,
          typename... TCases>
struct SeqHead_<Contianer<TH, TCases...>> {
  using type = TH;
};

template <typename TSeqCont>
using SeqHead = typename SeqHead_<TSeqCont>::value;

template <typename TSeqCont>
struct SeqTail_;

template <template <typename...> class Contianer,
          typename TH,
          typename... TCases>
struct SeqTail_<Contianer<TH, TCases...>> {
  using type = Contianer<TCases...>;
};

template <typename TSeqCont>
using SeqTail = typename SeqTail_<TSeqCont>::vail;

template <typename T>
constexpr static bool DependencyFalse = false;

template <typename T>
using RemConRef = std::remove_cv_t<std::remove_reference_t<T>>;
}  // namespace MetaNN

#endif /* __TRAITS__H__ */
