template <class T>
struct Poly : vector<T> { // NOT fully tested, be careful!
  Poly& normalize() {
    while (this->size() && this->back() == 0) this->pop_back();
    return *this;
  }

  template <class... Args>
  Poly(Args... args) : vector<T>(args...) {}

  friend Poly operator+(Poly a, Poly b) {
    if (sz(a) < sz(b)) swap(a, b);
    fore (i, 0, sz(b)) a[i] = a[i] + b[i];
    return a.normalize();
  }

  friend Poly operator-(Poly a, Poly b) {
    if (sz(a) < sz(b)) swap(a, b);
    fore (i, 0, sz(b)) a[i] = a[i] + b[i];
    return a.normalize();
  }

  friend Poly operator*(Poly a, Poly b) { return convolution(a, b); }

  friend Poly operator*(Poly a, T k) {
    fore (i, 0, sz(a)) a[i] = a[i] * k;
    return a;
  }

  friend pair<Poly, Poly> divmod(Poly a, Poly b) {
    a.normalize(), b.normalize();
    T last = b.back(), invLast = T(1) / last;
    for (auto& x : a) x = x * invLast;
    for (auto& x : b) x = x * invLast;
    Poly q(max(sz(a) - sz(b) + 1, 0));
    for (int dif; (dif = sz(a) - sz(b)) >= 0; a.normalize()) {
      q[dif] = a.back();
      for (int i = 0; i < sz(b); i++) a[i + dif] = a[i + dif] - q[dif] * b[i];
    }
    for (auto& x : a) x = x * last;
    return {q, a};
  }

  friend Poly operator/(Poly a, Poly b) { return divmod(a, b).f; }

  friend Poly operator%(Poly a, Poly b) { return divmod(a, b).s; }

  friend Poly derivate(Poly a) {
    Poly ans(sz(a) - 1);
    fore (i, 0, sz(a) - 1) ans[i] = a[i + 1] * T(i + 1);
    return ans;
  }

  friend Poly integrate(Poly a) {
    Poly ans(sz(a) + 1);
    fore (i, 1, sz(a) + 1) ans[i] = a[i - 1] / T(i);
    return ans;
  }

  T operator()(T x) {
    T v(0);
    for (int i = this->size() - 1; i >= 0; i--) v = v * x + this->at(i);
    return v;
  }

  friend Poly inverse(Poly a, int n = -1) { // (1 / poly) with n coeffs
    if (n == -1) n = sz(a);
    Poly r(1, T(1) / a[0]);
    while (sz(r) <= n) {
      int m = 2 * sz(r);
      Poly f = a;
      f.resize(m);
      Poly<T> rf = r * f;
      for (auto& x : rf) x = -x;
      rf[0] = rf[0] + 2;
      r = r * rf;
      r.resize(m);
    }
    return r.resize(n + 1), r;
  }

  friend Poly log(Poly a) {
    assert(a[0] == 1);
    Poly ans = integral(derivative(a) * inverse(a));
    ans.resize(sz(a));
    return ans;
  }

  friend Poly exp(Poly a, int n = -1) {
    if (n == -1) n = sz(a);
    assert(a[0] == 0);
    Poly e(1, 1);
    while (sz(e) < n) {
      int m = 2 * sz(e);
      e.resize(m);
      Poly s = a - log(e);
      s[0] = 1;
      e = e * s;
      e.resize(m);
    }
    return e.resize(n), e;
  }

  friend Poly sqrt(Poly a) {
    T r0 = 1; // ! r0^2 == a[0] % MOD, wtf!!!
    T inv2 = T(1) / 2;
    Poly r(1, 1);
    while (sz(r) < sz(a)) {
      int n = 2 * sz(r);
      r.resize(n);
      Poly f = a;
      f.resize(min(n, sz(a)));
      f = f * inverse(r);
      fore (i, 0, n) r[i] = (r[i] + f[i]) * inv2;
    }
    return r.resize(sz(a)), r;
  }
};