template <class T>
struct Berlekamp {
  int n;
  vector<T> s, t, pw[20];

  vector<T> combine(vector<T> a, vector<T> b) {
    vector<T> ans(sz(t) * 2 + 1);
    for (int i = 0; i <= sz(t); i++)
      for (int j = 0; j <= sz(t); j++) ans[i + j] += a[i] * b[j];
    for (int i = 2 * sz(t); i > sz(t); --i)
      for (int j = 0; j < sz(t); j++) ans[i - 1 - j] += ans[i] * t[j];
    ans.resize(sz(t) + 1);
    return ans;
  }

  Berlekamp(const vector<T>& s) : n(sz(s)), t(n), s(s) {
    vector<T> x(n), tmp;
    t[0] = x[0] = 1;
    T b = 1;
    int len = 0, m = 0;
    fore (i, 0, n) {
      ++m;
      T d = s[i];
      for (int j = 1; j <= len; j++) d += t[j] * s[i - j];
      if (d == 0)
        continue;
      tmp = t;
      T coef = d / b;
      for (int j = m; j < n; j++) t[j] -= coef * x[j - m];
      if (2 * len > i)
        continue;
      len = i + 1 - len;
      x = tmp;
      b = d;
      m = 0;
    }
    t.resize(len + 1);
    t.erase(t.begin());
    for (auto& x : t) x = -x;
    pw[0] = vector<T>(sz(t) + 1), pw[0][1] = 1;
    fore (i, 1, 20)
      pw[i] = combine(pw[i - 1], pw[i - 1]);
  }

  T operator[](lli k) {
    vector<T> ans(sz(t) + 1);
    ans[0] = 1;
    fore (i, 0, 20)
      if (k & (1LL << i))
        ans = combine(ans, pw[i]);
    T val = 0;
    fore (i, 0, sz(t))
      val += ans[i + 1] * s[i];
    return val;
  }
};