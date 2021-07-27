// maximize c^t x s.t. ax <= b, x >= 0
template <class T>
pair<T, vector<T>> simplex(vector<vector<T>> a, vector<T> b, vector<T> c) {
  const T EPS = 1e-9;
  T sum = 0;
  int n = b.size(), m = c.size();
  vector<int> p(m), q(n);
  iota(all(p), 0), iota(all(q), m);

  auto pivot = [&](int x, int y) {
    swap(p[y], q[x]);
    b[x] /= a[x][y];
    fore (i, 0, m) if (i != y) a[x][i] /= a[x][y];
    a[x][y] = 1 / a[x][y];
    fore (i, 0, n) if (i != x && abs(a[i][y]) > EPS) {
      b[i] -= a[i][y] * b[x];
      fore (j, 0, m) if (j != y) a[i][j] -= a[i][y] * a[x][j];
      a[i][y] = -a[i][y] * a[x][y];
    }
    sum += c[y] * b[x];
    fore (i, 0, m) if (i != y) c[i] -= c[y] * a[x][i];
    c[y] = -c[y] * a[x][y];
  };

  while (1) {
    int x = -1, y = -1;
    ld mn = -EPS;
    fore (i, 0, n) if (b[i] < mn) mn = b[i], x = i;
    if (x < 0) break;
    fore (i, 0, m) if (a[x][i] < -EPS) {
      y = i;
      break;
    }
    assert(y >= 0);  // no solution to Ax <= b
    pivot(x, y);
  }
  while (1) {
    int x = -1, y = -1;
    ld mx = EPS;
    fore (i, 0, m) if (c[i] > mx) mx = c[i], y = i;
    if (y < 0) break;
    ld mn = 1e200;
    fore(i, 0, n) if (a[i][y] > EPS && b[i] / a[i][y] < mn) {
      mn = b[i] / a[i][y], x = i;
    }
    assert(x >= 0);  // c^T x is unbounded
    pivot(x, y);
  }

  vector<T> ans(m); 
  fore(i, 0, n) if (q[i] < m) ans[q[i]] = b[i];
  return {sum, ans};
}
