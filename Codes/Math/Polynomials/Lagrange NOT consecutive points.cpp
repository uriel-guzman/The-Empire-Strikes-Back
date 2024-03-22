template <class T>
T Lagrange(vector<T>& x, vector<T>& y, lli k) { // O(sz(x) ^ 2)
  T ans = 0;
  fore (i, 0, sz(x)) {
    T num = 1, den = 1;
    fore (j, 0, sz(x)) {
      if (j == i) continue;
      num *= (T(k) - x[j]);
      den *= (x[i] - x[j]);
    }
    ans += y[i] * num / den;
  }
  return ans;
}