template <class T>
struct Lagrange {
  int n;
  vector<T> y, suf, fac;

  Lagrange(vector<T>& y) : n(sz(y)), y(y), suf(n + 1, 1), fac(n, 1) {
    fore (i, 1, n)
      fac[i] = fac[i - 1] * i;
  }

  T operator[](lli k) {
    for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] * (k - i);

    T pref = 1, val = 0;
    fore (i, 0, n) {
      T num = pref * suf[i + 1];
      T den = fac[i] * fac[n - 1 - i];
      if ((n - 1 - i) % 2)
        den *= -1;
      val += y[i] * num / den;
      pref *= (k - i);
    }
    return val;
  }
};