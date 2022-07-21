#include <vector> 
#include <cstdio> 
#include <iostream> 
#include <typeinfo> 

// 在c++ 17之前，总是必须显式地指定类模板的所有模板参数类型。
// c++ 17起，必须显式指定模板参数的约束得到了放宽。如果构造函数能够推导出所有模板参数，则可以跳过显式定义模板参数：
// 类模板参数推导（以下简称CTAD）有两个值得注意的地方


// 构造函数模版推导
// 在 C++17 前需要指明类型
// contruct pair

int main() {
  // C++11
  std::pair<int, float> old_cpp_1{1, 1.1};
  auto old_cpp_2 = std::make_pair(1, 1.1);
}
template <class _T1, class _T2>
inline pair<typename __unwrap_ref_decay<_T1>::type, typename __unwrap_ref_decay<_T2>::type>
make_pair(_T1&& __t1, _T2&& __t2) {
    return pair<typename __unwrap_ref_decay<_T1>::type, typename __unwrap_ref_decay<_T2>::type>
               (_VSTD::forward<_T1>(__t1), _VSTD::forward<_T2>(__t2));
}

// C++17 可以推导出类型

int main() {
  std::pair cpp17_1{1, 1.1};        // std::pair<int, double>
  std::vector cpp17_2 = {1, 2, 3};  // std::vector<int>
}

template<typename T>
class OK {
public:
  OK(T a) {
    printf("construct OK!\n");
  }
  ~OK(){}
};
int main() {
  OK a = {1};
}

int main() {
  // 注意点:
  // 1. vector并没有能够直接接受单个参数作为初始元素的构造函数。
  //    实参elem通过大括号传递给elems，用只有一个elem元素的初始化列表来初始化elems这个vector。
  std::vector one_element{1};
  std::cout << typeid(one_element).name() << std::endl;
}