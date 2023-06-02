template <class T>
struct Mat : vector<vector<T>> {
  int n, m;

  Mat(int n, int m) : vector<vector<T>>(n, vector<T>(m)), n(n), m(m) {}

  Mat<T> operator*(const Mat<T>& other) {
    assert(m == other.n);
    Mat<T> c(n, other.m);
    fore (k, 0, m)
      fore (i, 0, n)
        fore (j, 0, other.m)
          c[i][j] += (*this)[i][k] * other[k][j];
    return c;
  }

  Mat<T> pow(lli k) {
    assert(n == m);
    Mat<T> ans(n, n);
    fore (i, 0, n)
      ans[i][i] = 1;
    for (; k > 0; k >>= 1) {
      if (k & 1)
        ans = ans * *this;
      *this = *this * *this;
    }
    return ans;
  }
};
