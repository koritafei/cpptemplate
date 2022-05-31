/**
 * @file int_n.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief int_<N> 表示数值类型
 * @version 0.1
 * @date 2020-07-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/mpl/int.hpp>
#include <iostream>

namespace mpl         = boost::mpl;  // 命名空间别名
static int const five = mpl::int_<5>::value;

int main(int argc, char **argv) {
  std::cout << five << std::endl;
}
