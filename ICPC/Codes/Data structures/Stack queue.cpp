template <class T, class F = function<T(const T&, const T&)>>
struct Stack : vector<T> {
  vector<T> s;
  F f;

  Stack(const F& f) : f(f) {}

  void push(T x) {
    this->pb(x);
    s.pb(s.empty() ? x : f(s.back(), x));
  }

  T pop() {
    T x = this->back();
    this->pop_back();
    s.pop_back();
    return x;
  }

  T query() {
    return s.back();
  }
};

template <class T, class F = function<T(const T&, const T&)>>
struct Queue {
  Stack<T> a, b;
  F f;

  Queue(const F& f) : a(f), b(f), f(f) {}

  void push(T x) {
    b.push(x);
  }

  T pop() {
    if (a.empty())
      while (!b.empty())
        a.push(b.pop());
    return a.pop();
  }

  T query() {
    if (a.empty())
      return b.query();
    if (b.empty())
      return a.query();
    return f(a.query(), b.query());
  }
};
