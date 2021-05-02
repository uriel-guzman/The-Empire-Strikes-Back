template <class T,class F = function<T(const T&, const T&)>> 
struct FoldableDeque {
  vector<T> l, r, pref, suf;
  F f;

  FoldableDeque(const F &f) : f(f) {}
  FoldableDeque(const vector<T> &v, const F &f) : f(f) {
    build(v);
  }

  T query() { 
    T ans = pref.size() ? pref.back() : T();
    return suf.empty() ? ans : f(ans, suf.back());
  }

  void build(vector<T> v) {
    l = r = pref = suf = {};
    int n = v.size();
    for (int i = n / 2; i < n; ++i) push_back(v[i]);
    for (int i = n / 2; i--; ) push_front(v[i]);
  }

  void push_front(T a) { 
    l.push_back(a);
    pref.push_back(pref.empty() ? a : f(a, pref.back())); 
  }

  void push_back(T a) { 
    r.push_back(a); 
    suf.push_back(suf.empty() ? a : f(a, suf.back()));
  }

  void pop_front() {
    if (l.empty()) build({begin(r) + 1, end(r)});
    else l.pop_back(), pref.pop_back();
  }

  void pop_back() {
    if (r.empty()) build({rbegin(l), rend(l) - 1});
    else r.pop_back(), suf.pop_back();
  }
};