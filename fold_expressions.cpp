#include <iostream>
/*
使用折叠表达式可以简化对C++11中引入的参数包的处理，从而在某些情况下避免使用递归。

支持的操作符
折叠表达式支持 32 个操作符:
+, -, *, /, %, ^, &, |, =, <,
>, <<, >>, +=, -=, *=, /=, %=, ^=, &=, |=, <<=,
>>=,==, !=, <=, >=, &&, ||, ,, .*, ->*.

语法形式
折叠表达式共有四种语法形式。分别为一元的左折叠和右折叠，以及二元的左折叠和右折叠。
1、一元右折叠(unary right fold)
　　( pack op ... )
　　一元右折叠(E op ...)展开之后变为 E1 op (... op (EN-1 op EN))
2、一元左折叠(unary left fold)
　　( ... op pack )
　　一元左折叠(... op E)展开之后变为 ((E1 op E2) op ...) op EN
3、二元右折叠(binary right fold)
　　( pack op ... op init )
　　二元右折叠(E op ... op I)展开之后变为 E1 op (... op (EN−1 op (EN op I)))
4、二元左折叠(binary left fold)
　　( init op ... op pack )


语法形式中的op代表运算符，pack代表参数包，init代表初始值。

*/

#ifdef CPP11

// C++11, sum
template<typename First>
First AllSum(First&& first) {
  std::cout << "first" << std::endl;
  return first;
}
template<typename First, typename Second, typename... Rest>  
First AllSum(First&& first, Second&& second, Rest&&... rest) {  
  std::cout << "all sum" << std::endl;
  return AllSum(first + second, std::forward<Rest>(rest)...);  
}
int main() {
  std::cout << AllSum(1, 2, 3) << std::endl;
  return 0;
}

#endif
#undef CPP11

#ifdef CPP17
// 一元右折叠
// ( pack op ...) = (pack_1 op (... op (pack_N-1 op pack_N)))
template<typename... Args>
bool CheckTrueAll(Args... args) {
  std::cout << "unary right fold" << std::endl;
  return (args && ...);
}

// 一元左折叠
// ( ... op pack) = (((pack_1 op pack_2) op pack_3) ... op pack_N)
template<typename... Args>
int AddAll(Args... args) {
  std::cout << "unary left fold" << std::endl;
  return (... + args);
}

// 二元右折叠
// ( pack op ... op init) = (pack_1 op (... op (pack_N op init)))
template<typename First, typename... Rest>
bool CheckTrueAll(First&& first, Rest... rest) {
  std::cout << "binary right fold" << std::endl;
  return (rest && ... && first);
}

// 二元左折叠
// ( init op ... op pack) = (((init op pack_1) op pack_2) ... op pack_N)
template<typename First, typename... Rest>
First AddAll(First&& first, Rest&&... rest) {
  std::cout << "binary left fold" << std::endl;
  return (first + ... + rest);
}

int main() {
  std::cout << CheckTrueAll(true, true, true) << std::endl;
  std::cout << AddAll(1, 2, 3) << std::endl;
  std::cout << CheckTrueAll(true, true, true) << std::endl;
  std::cout << AddAll(1, 2, 3) << std::endl;
  return 0;
}
#endif
#undef CPP17