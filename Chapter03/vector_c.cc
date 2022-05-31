/**
 * @file vector_c.cc
 * @author koritafei (koritafei@gmail.com)
 * @brief 整型序列外覆类
 * @version 0.1
 * @date 2020-07-15
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <boost/mpl/vector_c.hpp>

typedef boost::mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0> mass;
typedef boost::mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0> length;
typedef boost::mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0> time;
typedef boost::mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0> charge;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0> temperature;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0> intensity;
typedef boost::mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

template <typename T, typename Dimensions>
struct quantity {
  explicit quantity(T x) : m_value(x) {}

  T get_value() {
    return m_value;
  }

 private:
  T m_value;
};

int main(int argc, char **argv) {
  quantity<float, length> l(1.0f);  // length
  quantity<float, mass>   m(2.0f);  // mass
}
