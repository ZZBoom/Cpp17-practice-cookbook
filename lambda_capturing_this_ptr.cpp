#include <string>
#include <iostream>

// 当在成员函数中使用lambda时，您不能隐式地访问调用成员函数的对象。
// 也就是说，在lambda内部，如果不以任何形式捕获它，就不能使用对象的成员(独立于是否用this->限定它们):

#ifdef EXP1
// g++ -std=c++14 -g lambda_capturing_this_ptr.cpp -DEXP1
class Example {
public:
  Example(std::string name) : name_(name) {}
  void Func() {
    // error: 'this' cannot be implicitly captured in this context
    auto lambda_1 = [] () { std::cout << name_ << std::endl;};
    auto lambda_2 = [] () { std::cout << this->name_ << std::endl;};
  }
private:
  std::string name_;
};
#endif
#undef EXP1

#ifdef EXP2
// g++ -std=c++14 -g lambda_capturing_this_ptr.cpp -DEXP2
// C++11, C++14, 您必须通过值或引用传递此值:
// 即使进行了this捕获，也是通过引用捕获了底层对象(因为只复制了this指针)。
// 如果lambda的生存期超过调用成员函数的对象的生存期，，这就会成为一个问题。
// 一个关键的例子是当lambda定义一个新线程的任务时，该线程应该使用它自己的对象副本来避免任何并发性或生存期问题。
class Example {
public:
  Example(std::string name) : name_(name) {}
  void Func() {
    auto lambda_1 = [this] () { std::cout << name_ << std::endl;};
    auto lambda_2 = [=] () { std::cout << name_ << std::endl;};
    auto lambda_3 = [&] () { std::cout << name_ << std::endl;};
  }

private:
  std::string name_;
};
#endif
#undef EXP2

#ifdef EXP3
// g++ -std=c++14 -g lambda_capturing_this_ptr.cpp -DEXP3
// 虽然满足了我们的期望，但是它的可读性差。而且，程序员在使用=或&捕获其他对象时仍然可能意外地使用name这个变量:
class Example {
public:
  Example(std::string name) : name_(name) {}
  void Func() {
    auto lambda = [=, this_bak = *this] () { 
      this_bak.name_ = "hi world";
      std::cout << this_bak.name_ << std::endl;
      std::cout << name_ << std::endl;
      name_ = "hello world 2";
      std::cout << this_bak.name_ << std::endl;
      std::cout << name_ << std::endl;
    };
    lambda();
  }

  void Pname() {
    std::cout << name_ << std::endl;
  }

private:
  mutable std::string name_;
};
#endif
#undef EXP3

#ifdef EXP4
// g++ -std=c++17 -g lambda_capturing_this_ptr.cpp -DEXP4
// 从c++ 17，你可以显式地要求捕获当前对象的副本，方法是捕获*this:
class Example {
public:
  Example(std::string name) : name_(name) {}
  void Func() {
    auto lambda = [*this] () { 
      std::cout << name_ << std::endl;
      name_ = "hello world 2";
      std::cout << name_ << std::endl;
    };
    lambda();
  }

  void Pname() {
    std::cout << name_ << std::endl;
  }

private:
  mutable std::string name_;
};
#endif
#undef EXP4

#ifdef EXP5
// g++ -std=c++17 -g lambda_capturing_this_ptr.cpp -DEXP5
class Example {
public:
  Example(std::string name) : name_(name) {}
  void Func() {
    auto lambda1 = [*this] () { };
    auto lambda2 = [&, *this] () { };
    auto lambda2 = [=, *this] () { };
    auto lambda3 = [this, *this] () { }; // error: 'this' can appear only once in a capture list
  }

  void Pname() {
    std::cout << name_ << std::endl;
  }

private:
  mutable std::string name_;
};
#endif
#undef EXP5

int main() {
  Example exp("hello world");
  exp.Func();
  exp.Pname();
}