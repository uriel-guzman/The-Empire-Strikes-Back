template <class T, class F = function<T(const T&, const T&)>>
struct Stack {
  vector<T> s, t;
  F f;
  
  Stack(const F &f) : f(f) {}

  void push(T x) {
    s.pb(x);
    t.pb(t.empty() ? x : f(t.back(), x));
  }

  T pop() {
    T x = s.back();
    s.pop_back();
    t.pop_back();
    return x;
  }

  bool empty() {
    return s.empty();
  }

  T query() {
    return t.back();
  }
};

template <class T, class F = function<T(const T&, const T&)>>
struct Queue {
  Stack<T> a, b;
  F f;

  Queue(const F &f) : a(f), b(f), f(f) {}

  void push(T x) {
    b.push(x);
  }

  void pop() {
    if (a.empty())
      while (!b.empty())
        a.push(b.pop());
    a.pop();
  }

  T query() {
    if (a.empty()) return b.query();
    if (b.empty()) return a.query();
    return f(a.query(), b.query());
  }
};

