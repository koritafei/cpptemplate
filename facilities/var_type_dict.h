#ifndef __VAR_TYPE_DICT__H__
#define __VAR_TYPE_DICT__H__

#include <iostream>
#include <memory>
#include <type_traits>

#include "null_param.h"
#include "traits.h"

namespace MetaNN {

namespace NSMultiTypeDict {
/**
 * @brief
 * @tparam N 构造的元素数目
 * @tparam TCont 容器类型，用于存储最终的结果(值为类型数组)
 * @tparam T 已生成的类型序列
 * */
template <size_t N, template <typename...> class TCont, typename... T>
struct Create_ {
  using type = typename Create_<N - 1, TCont, NullParameter, T...>::type;
};

template <template <typename...> class TCont, typename... T>
struct Create_<0, TCont, T...> {
  using type = TCont<T...>;
};

template <typename TFindTag, size_t N, typename TCurTag, typename... TTags>
struct Tag2ID_ {
  constexpr static size_t value = Tag2ID_<TFindTag, N + 1, TTags...>::value;
};

template <typename TFindTag, size_t N, typename... TTags>
struct Tag2ID_<TFindTag, N, TFindTag, TTags...> {
  constexpr static size_t value = N;
};

template <typename TFindTag, typename... TTags>
constexpr size_t Tag2ID = Tag2ID_<TFindTag, 0, TTags...>::value;

/**
 * @brief
 * @tparam TVal 替换的目标数据类型
 * @tparam N 目标类型在类型数组中的位置
 * @tparam M 辅助变量，已经扫描的类型个数
 * @tparam TProcessedTypes 数组容器包含了已经完成扫描的部分
 * @tparam TRemainTypes 包含了还需要进行扫描替换的部分
 * */
template <typename TVal,
          size_t N,
          size_t M,
          typename TProcessedTypes,
          typename... TRemainTypes>
struct NewTupleType_;

/**
 * @brief 处理N != M 的情况，
 * @tparam TVal
 * @tparam N
 * @tparam M
 * @tparam TCont // 已经完成替换扫描的类型
 * @tparam TModifiedTypes
 * @tparam TCurType 当前处理类型
 * @tparam TRemainTypes 未处理类型
 * */
template <typename TVal,
          size_t N,
          size_t M,
          template <typename...>
          class TCont,
          typename... TModifiedTypes,
          typename TCurType,
          typename... TRemainTypes>
struct NewTupleType_<TVal,
                     N,
                     M,
                     TCont<TModifiedTypes...>,
                     TCurType,
                     TRemainTypes...> {
  using type = typename NewTupleType_<TVal,
                                      N,
                                      M + 1,
                                      TCont<TModifiedTypes..., TCurType>,
                                      TRemainTypes...>::type;
};

/**
 * @brief 处理 N==M的情况
 * @tparam TVal
 * @tparam N
 * @tparam TCont
 * @tparam TModifiedTypes
 * @tparam TCurType
 * @tparam TRemainTypes
 * */
template <typename TVal,
          size_t N,
          template <typename...>
          class TCont,
          typename... TModifiedTypes,
          typename TCurType,
          typename... TRemainTypes>
struct NewTupleType_<TVal,
                     N,
                     N,
                     TCont<TModifiedTypes...>,
                     TCurType,
                     TRemainTypes...> {
  using type = TCont<TModifiedTypes..., TVal, TRemainTypes...>;
};

template <typename TVal,
          size_t TagPos,
          typename TCont,
          typename... TRemainTypes>
using NewTupleType =
    typename NewTupleType_<TVal, TagPos, 0, TCont, TRemainTypes...>::type;

template <size_t Pos, typename... TTags>
struct Pos2Type_ {
  static_assert((Pos != 0), "Invalid position.");
};

template <size_t Pos, typename TCur, typename... TTags>
struct Pos2Type_<Pos, TCur, TTags...> {
  using type = typename std::conditional_t<(Pos == 0),
                                           Identity_<TCur>,
                                           Pos2Type_<Pos - 1, TTags...>>::type;
};

template <size_t Pos, typename... TTags>
using Pos2Type = typename Pos2Type_<Pos, TTags...>::type;
}  // namespace NSMultiTypeDict

template <typename... TParamters>
struct VarTypeDict {
  template <typename... TTypes>
  struct Values {
  public:
    Values() = default;

    Values(std::shared_ptr<void>(&&input)[sizeof...(TTypes)]) {
      for (size_t i = 0; i < sizeof...(TTypes); ++i) {
        m_truple[i] = std::move(input[i]);
      }
    }

    template <typename TTag, typename TVal>
    auto Set(TVal &&val) && {
      constexpr static size_t TagPos =
          NSMultiTypeDict::Tag2ID<TTag, TParamters...>;

      using rawVal = std::decay_t<TVal>;
      rawVal *tmp  = new rawVal(std::forward<TVal>(val));

      m_truple[TagPos] = std::shared_ptr<void>(tmp, [&](void *ptr) {
        rawVal *nptr = static_cast<rawVal *>(ptr);
        delete nptr;
      });

      using new_type =
          NSMultiTypeDict::NewTupleType<rawVal, TagPos, Values<>, TTypes...>;
      return new_type(std::move(m_truple));
    }

    template <typename TTag>
    auto &Get() const {
      constexpr static size_t TagPos =
          NSMultiTypeDict::Tag2ID<TTag, TParamters...>;
      using AimType = NSMultiTypeDict::Pos2Type<TagPos, TTypes...>;

      void    *tmp = m_truple[TagPos].get();
      AimType *res = static_cast<AimType *>(tmp);
      return *res;
    }

    template <typename TTags>
    using ValueType =
        NSMultiTypeDict::Pos2Type<NSMultiTypeDict::Tag2ID<TTags, TParamters...>,
                                  TTypes...>;

  private:
    std::shared_ptr<void> m_truple[sizeof...(TTypes)];
  };

public:
  static auto Create() {
    using type =
        typename NSMultiTypeDict::Create_<sizeof...(TParamters), Values>::type;

    return type{};
  }
};

}  // namespace MetaNN

#endif /* __VAR_TYPE_DICT__H__ */
