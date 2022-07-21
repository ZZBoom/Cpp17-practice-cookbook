#include <array>
#include <cstdio>
#include <iostream>
/*

constexpr 函数中用lambda表达式了，这在C++17之前是不允许的。

constexpr函数有如下限制：
lambda表达式内没有静态变量；
lambda表达式内没有虚函数；
lambda表达式内没有 try/catch语句；
lambda表达式内没有new/delete；

*/


int main() {
  // C++17前lambda表达式只能在运行时使用，C++17引入了constexpr lambda表达式，可以用于在编译期进行计算。
  // static_assert 这个关键字，用来做编译期间的断言，因此叫做静态断言。
  constexpr auto squared = [] (int n) { return n * n; };
  static_assert(squared(3) == 9, "a");
  std::array<int, squared(5)> arr;
  printf("%zd\n", arr.size());

  // 从c++17起，如果lambda表达式符合编译时期constexpr的要求的话，lambdas会隐式转换为constexpr表达式。
  auto non_constexpr_lambda = [] (int y) {
    static int x = 1;
    return x + y;
  };
  std::array<int, non_constexpr_lambda(5)> boom; // ERROR, static variable in compile-time context
  std::cout << non_constexpr_lambda(2) << std::endl; // OK

  // 对于lambda表达式，如果声明了constexpr但是又使用了不满足constexpr lambda的语句，则为编译错误：

  // error: static variable not permitted in a constexpr function
  auto set_constexpr_but_unexpected_lambda = [] (int y) constexpr {
    static int x = 1;
    return x + y;
  };
}

// constexpr lambda 也就意味着还可以在 constexpr 函数中用lambda表达式了，
template<typename T>
constexpr auto func(T a) {
  return [a](int b) {return a + b;};
}
int main() {
  const auto what = func(1)(2);
  std::cout << what << std::endl;
  return 0;
}