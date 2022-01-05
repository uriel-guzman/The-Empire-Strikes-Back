template <class T>
using Mat = vector<vector<T>>;

template <class T>
Mat<T> operator*(Mat<T>& a, Mat<T>& b) {
  Mat<T> c(sz(a), vector<T>(sz(b[0])));
  fore (k, 0, sz(a[0]))
    fore (i, 0, sz(a))
      fore (j, 0, sz(b[0]))
        c[i][j] += a[i][k] * b[k][j];
  return c;
}

template <class T>
vector<T> operator*(Mat<T>& a, vector<T>& b) {
  assert(sz(a[0]) == sz(b));
  vector<T> c(sz(a), T());
  fore (i, 0, sz(a))
    fore (j, 0, sz(b))
      c[i] += a[i][j] * b[j];
  return c;
}

template <class T>
Mat<T> fpow(Mat<T>& a, lli n) {
  Mat<T> ans(sz(a), vector<T>(sz(a)));
  fore (i, 0, sz(a))
    ans[i][i] = 1;
  for (; n > 0; n >>= 1) {
    if (n & 1)
      ans = ans * a;
    a = a * a;
  }
  return ans;
}
