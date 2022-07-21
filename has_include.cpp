#include <cstdio>  // for printf

#ifdef __has_include
#ifdef EXP1
#if __has_include("example.h")
#include "example.h"
#else
#error "cannot find example.h"
#endif
#endif
#undef EXP1

#ifdef EXP2
// 我们能用 __has_include 表达式侦测某个头文件（Header File）是否存在。
int main() {
#if __has_include(<cstdio>)
    printf("has cstdio\n");
#endif

#if __has_include(<iostream>)
    printf("has iostream\n");
#endif

#if __has_include(<haha>)
    printf("has haha\n");
#endif
    return 0;
}
#endif
#undef EXP2

/*
以上程式碼中，我們先以 defined(__has_include) 檢查前置處理器是否支援 __has_include 表達式。
支援 C++ 17 的編譯器必須回傳 1。部分編譯器（例如：Clang）在 C++ 17 以前就以語言擴充（Language Extension）的形式支援 __has_include 表達式，所以我們是以 defined(__has_include) 檢查支援度。
接著，我們以 __has_include(<optional>) 偵測 <optional> 標頭檔。
如果有找到，則直接使用標準函式庫的 std::optional，並以 using 宣告將 optional 引入視野（Scope）。如果沒有找到，則使用 Boost 函式庫的 boost::optional，它與標準函式庫 std::optional 相似，可以作為 std::optional 在 C++ 14 的替代品。
*/
// #ifdef EXP3

#if defined(__has_include) && __has_include(<optional>)
#include <optional>
#pragma message('c++17 optional header')
using std::optional;
#else
#include <boost/optional/optional.hpp>
using boost::optional;
#pragma message('boost optional header')
#endif

int main() {
  optional<int> x;
}
#endif
#undef EXP3
#endif