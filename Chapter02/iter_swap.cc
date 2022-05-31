/**
 * @file iter_swap.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief 模板元类型推导
 * @version 0.1
 * @date 2020-07-13
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

template <typename ForwardIterator1, typename ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2) {
  typename ForwardIterator1::value_type tmp = *i1;
  *i1                                       = *i2;
  tmp                                       = *i1;
}

template <typename ForwardIterator1, typename ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2) {
  typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
  *i1                                                             = *i2;
  *i2                                                             = tmp;
}
