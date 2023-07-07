#include <iostream>
#include <memory>
using namespace std;

class A {
 public:
  A(int _i) : m_i(_i) { cout << "A(int _i) " << m_i << endl; }
  A(A& a) : m_i(a.m_i) { cout << "A(A& a) " << a.m_i << endl; }
  // A(A& a) = delete;
  A(A&& a) : m_i(a.m_i) { cout << "A(A&& a) " << a.m_i << endl; }
  // A(A&& a) = delete;
  int m_i;
};

template <class T>
decltype(auto) forwardWrapper(T&& arg) {
  return forward<T>(arg);
}

A fun(int i) {
  cout << "begin fun" << endl;
  A a1(111);
  A a2(222);
  if (i == 1) {
    cout << hex << &a1 << endl << dec;
    return forwardWrapper(a1);  // A(A& a) 构造发生在被调用处，即fun内部
  } else if (i == 2) {
    return a2;  // A(A&& a)
  } else {
    return A(333);  // A(A&& a)
  }
}

void fun1() {
  int i = 456;
  int j = 789;
  cout << i + j << endl;
}

A& fun2() { return *new A(111); }

void testRefer(A&) { cout << "The expression type is A&" << endl; }

void testRefer(A&&) { cout << "The expression type is A&&" << endl; }

int main(int argc, char* argv[]) {
  // int i;
  // A a = fun(argc);
  // int j;
  // cout << hex << &i << endl << dec;
  // cout << hex << &a << endl << dec;
  // cout << hex << &j << endl << dec;
  // fun1();
  // cout << a.m_i << endl;
  // A a1(111);
  // A a2 = std::move(a1);
  // A& a3 = fun2();
  A a4 = fun(1); //构造发生在被调用处，即fun内部，而不是这里
  cout << hex << &a4 << endl << dec;
  A a5 = fun(2);
  fun(3);
  // testRefer(std::move(a4));
  // cout << &fun(1) << endl;
  return 0;
}
