/**
 * @file binary.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief 第一个template程序
 * @version 0.1
 * @date 2020-07-13
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <iostream>

template <unsigned long N>
struct binary {
  static unsigned const value =
      binary<N / 10>::value * 2 + N % 10;  // 将高位移动到低位
};

// 特化
template <>
struct binary<0> {  // 递归终结
  static unsigned const value = 0;
};

int main(int argc, char **argv) {
  unsigned const one   = binary<1>::value;
  unsigned const three = binary<11>::value;
  unsigned const five  = binary<101>::value;
  unsigned const seven = binary<111>::value;
  unsigned const nine  = binary<1001>::value;

  std::cout << "one is " << one << std::endl;
  std::cout << "three is " << three << std::endl;
  std::cout << "five is " << five << std::endl;
  std::cout << "seven is " << seven << std::endl;
  std::cout << "nine is " << nine << std::endl;
}
