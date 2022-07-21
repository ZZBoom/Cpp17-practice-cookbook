#include <cstdio>

#ifdef EXP0
void f(int n) {
  switch (n) 
  {
    case 1:
      break;
    case 2:  // compiler may warn on fallthrough
      printf("h\n");
    case 3:  // compiler may warn on fallthrough
      printf("i\n");
    case 4:  // compiler may warn on fallthrough
      printf("j\n");
  }
}
#endif
#undef EXP0

// New attributes
// 为了处理编译器警告, fallthrough, nodiscard, maybe_unused
// fallthrough
#ifdef EXP1
void f(int n) 
{
  void g(), h(), i();
  switch (n) 
  {
    case 1:
    case 2:
      g();
      [[fallthrough]];
    case 3: // no warning on fallthrough
      h();
    case 4: // compiler may warn on fallthrough
      i();
      [[fallthrough]]; // ill­formed, not before a case label
  }
}
#endif
#undef EXP1

#ifdef EXP2
// [[nodiscard]] ：表示修饰的内容不能被忽略，可用于修饰函数，标明返回值一定要被处理
[[nodiscard]] int func() { return 1; };
void F() {
    // warning 没有处理函数返回值
    func();
}
// warning: ignoring return value of function declared with 'nodiscard' attribute [-Wunused-result]
#endif
#undef EXP2

#ifdef EXP3
maybe_unused
void f([[maybe_unused]] bool thing1,
       [[maybe_unused]] bool thing2)
{
   [[maybe_unused]] bool b = thing1;
   assert(b); // in release mode, assert is compiled out
}
#endif
#undef EXP3

int main() {

}