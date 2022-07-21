// 结构化绑定声明（Structured Binding Declaration）

#include <string>
#include <map>
#include <assert.h>
#include <typeinfo> 
#include <iostream> 


// 我们可以将一个MyStruct对象绑定到两个变量上。

struct MyStruct {
  int i = 0;
  std::string s;
};

int main() {
  MyStruct my_struct;
  auto [a, b] = my_struct;
}

// 增加代码可读性
int main() {
  std::map<int, std::string> my_map = {{1, "zsq"}, {2, "zsy"}, {3, "zqy"}};
  for (const auto& [key, value] : my_map) {
    // ...
  }
  auto [pos, ok] = my_map.insert({4, "new"});
  if (!ok) {
    // if insert failed, handle error using iterator pos:
  }
}


#define aliasname auto&

// 匿名变量

struct MyStruct {
  int i = 0;
  std::string s;
};
int main() {
  MyStruct my_struct;
  auto [a, b] = my_struct;
  // 等价于
  auto e = my_struct; // e是匿名变量
  // 匿名变量e的生命周期同结构化绑定的存活时间一样，当结构化绑定离开作用域时，e会同时析构。
  auto& u = e.i;
  auto& v = e.s;
}

// 内存地址和对齐也是存在。如果成员有对齐，结构化绑定也会存在对齐

struct MyStruct {
  int i = 0;
  std::string s;
};
int main() {
  MyStruct my_struct;
  auto [a, b] = my_struct;
  auto a_b_addr = (MyStruct*)&a;
  assert(&(a_b_addr->i) == &a);
  assert(&(a_b_addr->s) == &b);
} 

// 修饰符修饰的是匿名变量，而不是结构化绑定。
struct S {
  S():x("abcde"), y("ab") {}
  const char x[6];
  const char y[3];
};
int main() {
  S s1;
  auto [x, y] = s1;
  // A6_c, 
  std::cout << typeid(x).name() << std::endl;
  auto x_0 = x;
  // PKc, const char*
  // P is the encoding for "pointer", K refers to "const", and c means "char".
  std::cout << typeid(x_0).name() << std::endl;
} 

// 移动语义
// 结构化绑定u和v指向匿名变量中的成员，该匿名变量是my_struct的右值引用。my_struct仍然持有它的值:
struct MyStruct {
  int i = 0;
  std::string s;
};
int main() {
  MyStruct my_struct = {42, "Jim"};
  auto&& [u, v] = std::move(my_struct);
  // 等价于
  auto&& e = std::move(my_struct);
  aliasname a = e.i;
  aliasname b = e.s;

  MyStruct ms1 = {42, "Jim"};
  auto [u1, v1] = std::move(ms1);                // new entity with moved-from values from ms
  std::cout << "ms1.s: " << ms1.s << std::endl;  // prints unspecified value
  std::cout << "v1: " << v1 << std::endl;        // prints "Jim"
}