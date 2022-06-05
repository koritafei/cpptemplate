#include <iostream>
#include <map>

float func(std::map<std::string, float> &params) {
  auto first  = params.find("a");
  auto second = params.find("b");
  auto weight = params.find("weight");

  return (first->second * weight->second) +
         (second->second * (1 - weight->second));
}

int main() {
  std::map<std::string, float> params;
  params["a"]      = 1.2f;
  params["b"]      = 2.3f;
  params["weight"] = 4.5f;

  std::cout << func(params) << std::endl;
}
