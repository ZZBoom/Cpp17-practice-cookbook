#include <iostream>
#include <optional>
// 表达“有时存在”
// 在程序中，有时我们需要变量来表达“nothing”的意思，
// 比如你怎么写一个函数来“有可能“返回一个值？就好像给我找出一段文字中的第一个偶数，如果有的话，那很好；没有的话，也没什么大不了的——这都是很平凡也很常见的需求。

// 1. 以前我们常采用的做法是“magic value” ：
int find_index(); // a return value of -1 means no even number

// 
// 2. 变量需要同时绑定一个布尔值，在使用变量前先查询这个bool变量，看这个值是否存在；如果是，那么进行第二次访问获取这个变量的值。
std::pair<int, bool> find_index();

// 

// C++17 在 STL 中引入了std::optional<T>
// std::optional<T>类型的变量要么是一个T类型的变量，要么是一个表示“什么都没有”的状态。
// 这个状态也有自己的类型和值：类型是std::nullopt_t，值为std::nullopt。看起来是不是很熟悉？没错，概念上它和nullptr十分相似，区别就是后者是一个关键字罢了。

#ifdef ERROR
// 使用optional包装原始类型意味着需要存储原始类型的空间和额外的boolean flag，
// 因此optional对象将占有更多的内存空间。此外，optional对象的内存排列须遵循与内部对象一致的内存对齐准则。

template<typename T>
class optional {
  bool _initialized;
  std::aligned_storage_t<sizeof(T), alignof(T)> _strorage;
public:
// operations
};

#endif
#undef ERROR

// EXP1
#ifdef EXP1

std::optional<int> GetIndex(int x) {
  if (x > 0) {
    return x + 2;
  } else {
    return std::nullopt;
  }
}
int main() {
  auto ret = GetIndex(2);
  if (ret.has_value()) {
    std::cout << ret.value() << std::endl;
  } else {
    std::cout << "null" << std::endl;
  }
}

#endif
#undef EXP1

#ifdef EXP2

std::optional<std::string> GetName() {
  std::string name = "zsq";
  return name;       // move
  // return {name};  // copy
}
int main() {
  GetName();
}
#endif
#undef EXP2

#ifdef EXP3
class Sample {
public:
  Sample() : name_("sample") {} 
  Sample(std::string &name) : name_(name) {} 
private:
  std::string name_;
};
int main() {
  // EXP3: 原地构造
  std::optional<Sample> s1(std::in_place);
  auto s2 = std::make_optional<Sample>();
  std::string param = "haha";
  std::optional<Sample> s3(std::in_place, param);
  return 0;
}
#endif
#undef EXP3

// #ifdef EXP4
// non-copyable/movable类型

class Sample {
public:
  Sample() : name_("sample") {} 
  Sample(const Sample&) = delete;
  Sample& operator=(const Sample&) = delete;
  Sample(Sample &&) = delete;
  Sample& operator=(Sample &&) = delete;
private:
  std::string name_;
};
int main() {
  std::optional<Sample> s(std::in_place);
  auto ss = std::make_optional<Sample>();
  return 0;
}

// #endif
// #undef EXP4