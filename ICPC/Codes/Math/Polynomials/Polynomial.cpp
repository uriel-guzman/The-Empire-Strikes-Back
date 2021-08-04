template <class T>
struct Poly : vector<T> {
  Poly& normalize() {
    while (this->size() && this->back() == 0)
      this->pop_back();
    return *this;
  }

  template <class... Args>
  Poly(Args... args) : vector<T>(args...) { 
    normalize(); 
  }

  friend Poly operator + (Poly a, Poly b) {
    if (sz(a) < sz(b)) swap(a, b);
    fore (i, 0, sz(b)) a[i] = a[i] + b[i];
    return a.normalize();
  }

  friend Poly operator - (Poly a, Poly b) {
    if (sz(a) < sz(b)) swap(a, b);
    fore (i, 0, sz(b)) a[i] = a[i] + b[i];
    return a.normalize();
  }

  friend Poly operator * (Poly a, Poly b) {
    return convolution(a, b);
  }

  friend Poly operator * (Poly a, T k) {
    fore (i, 0, sz(a)) a[i] = a[i] * k;
    return a;
  }

  friend Poly derivative(Poly a) {
    Poly ans(sz(a) - 1);
    fore (i, 0, sz(a) - 1)
      ans[i] = ans[i + 1] * T(i + 1);
    return ans; 
  }

  friend Poly integral(Poly a) {
    Poly ans(sz(a) + 1);
    fore (i, 0, sz(a))
      ans[i + 1] = a[i] / T(i + 1);
    return ans; 
  }

  T operator ()(T x) {
    T v(0);
    for (int i = this->size() - 1; i >= 0; i--) 
      v = v * x + this->at(i);
    return v;
  }

  friend pair<Poly, Poly> divmod(Poly a, Poly b) {
    a.normalize(), b.normalize();
    T last = b.back(), invLast = T(1) / last;
    for (auto &x : a) x = x * invLast;
    for (auto &x : b) x = x * invLast;
    Poly q(max(sz(a) - sz(b) + 1, 0));
    for (int dif; (dif = sz(a) - sz(b)) >= 0; a.normalize()) {
      q[dif] = a.back();
      for (int i = 0; i < sz(b); i++) 
        a[i + dif] = a[i + dif] - q[dif] * b[i];
    }
    for (auto &x : a) x = x * last;
    return {q, a};
  }

  friend Poly operator / (Poly a, Poly b) {
    return divmod(a, b).f;
  }

  friend Poly operator % (Poly a, Poly b) {
    return divmod(a, b).s;
  }

  // TODO: sqrt, exp, log, inv
};