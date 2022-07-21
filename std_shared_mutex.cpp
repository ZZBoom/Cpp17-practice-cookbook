// https://cloud.tencent.com/developer/article/1353506
// shared_mutex是 c++的原生读写锁实现，有共享和独占两种锁模式，适用于并发高的读场景下，通过 reader 之前共享锁来提升性能。
// 在 c++17 之前，只能自己通过独占锁和条件变量自己实现读写锁或使用
// c++14 加入的性能较差的std::shared_timed_mutex。
// 以下是通过shared_mutex实现的线程安全计数器：

// C++ mutex
// 调用线程从成功调用lock()或try_lock()开始，到unlock()为止占有mutex对象。
// 当存在某线程占有mutex时，所有其他线程若调用lock则会阻塞，而调用try_lockh会得到false返回值。
// 由上述代码可以看到，通过mutex加锁的方式，来确保只有单一线程对临界区的资源进行操作。

// time_mutex则是进行加锁时可以设置阻塞的时间，若超过对应时长，则返回false。
// recursive_mutex则让单一线程可以多次对同一互斥量加锁，同样，解锁时也需要释放相同多次的锁。
#include <mutex>
#include <iostream>        // cout header
#include <shared_mutex>    // shared_mutex header
#include <thread>          // thread header

#ifdef EXP1
long num = 0;
std::mutex num_mutex;

void numplus() {
    num_mutex.lock();
    for (long i = 0; i < 1000000; ++i) {
        num++;
    }
    num_mutex.unlock();
};

void numsub() {
    num_mutex.lock();
    for (long i = 0; i < 1000000; ++i) {
        num--;
    }
    num_mutex.unlock();
}

int main() {
    std::thread t1(numplus);
    std::thread t2(numsub);
    t1.join();
    t2.join();
    std::cout << num << std::endl;
}
#endif
#undef EXP1

// 在C++之中并不提倡我们直接对锁进行操作，因为在lock之后忘记调用unlock很容易造成死锁。
// 而对临界资源进行操作时，可能会抛出异常，程序也有可能break，return 甚至 goto，这些情况都极容易导致unlock没有被调用。
// 所以C++之中通过RAII来解决这个问题，它提供了一系列的通用管理互斥量的类：
#ifdef EXP2
long num = 0;
std::mutex num_mutex;

void numplus() {
    std::lock_guard<std::mutex> lock_guard(num_mutex);
    for (long i = 0; i < 1000000; ++i) {
        num++;
    }
};
void numsub() {
    std::lock_guard<std::mutex> lock_guard(num_mutex);
    for (long i = 0; i < 1000000; ++i) {
        num--;
    }
}

int main() {
    std::thread t1(numplus);
    std::thread t2(numsub);
    t1.join();
    t2.join();
    std::cout << num << std::endl;
}
#endif
#undef EXP2


#ifdef EXP3
// 简单来说：
//  shared_lock是读锁。被锁后仍允许其他线程执行同样被shared_lock的代码
//  unique_lock是写锁。被锁后不允许其他线程执行被shared_lock或unique_lock的代码。它可以同时限制unique_lock与share_lock
long num = 0;
std::shared_mutex num_mutex;

// 仅有单个线程可以写num的值。
void numplus() {
    std::unique_lock<std::shared_mutex> lock_guard(num_mutex);
    for (long i = 0; i < 1000000; ++i) {
        num++;
    }
};

// 多个线程同时读num的值。
long numprint() {
    std::shared_lock<std::shared_mutex> lock_guard(num_mutex);
    return num;
}

int main() {
    std::thread t1(numplus);
    t1.join();
    std::cout << numprint() << std::endl;
}
#endif
#undef EXP3

// scope lock
// 当我们要进行多个锁管理时，很容易出现问题，由于加锁的先后顺序不同导致死锁。
#ifdef EXP4
std::mutex m1, m2;
// thread 1
{
  std::lock_guard<std::mutex> lock1(m1);
  std::lock_guard<std::mutex> lock2(m2);
}
// thread 2
{
  std::lock_guard<std::mutex> lock2(m2);
  std::lock_guard<std::mutex> lock1(m1);
}
std::mutex m1, m2;
// thread 1
{
  std::scope_lock lock(m1, m2);
}
// thread 2
{
  std::scope_lock lock(m1, m2);
}

#endif
#undef EXP4