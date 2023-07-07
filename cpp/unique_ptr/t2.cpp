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

unique_ptr<A> fun(int i) {
  cout << "begin fun" << endl;
  unique_ptr<A> a1 = make_unique<A>(111);
  unique_ptr<A> a2 = make_unique<A>(222);
  if (i == 1) {
    cout << hex << &a1 << endl << dec;
    return forwardWrapper(a1);
  } else if (i == 2) {
    return a2;
  } else {
    return make_unique<A>(333);
  }
}

int main() {
  fun(1);
  fun(2);
  fun(3);
  return 0;
}
