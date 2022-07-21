// #ifdef EXP0
// 简便的定义嵌套的命名空间.
// Nested namespaces

namespace A { namespace B { namespace C {
// ...
} } }

namespace A::B::C {
// ...
}


#endif
// #undef EXP0

int main() {

}