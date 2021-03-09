template <class C>
pair<C, vi> Hungarian(vector<vector<C>> &a) {
  int n = sz(a), m = sz(a[0]), p, q, j, k; // n <= m
 vector<C> fx(n, numeric_limits<C>::min()), fy(m, 0);
  vi x(n, -1), y(m, -1);
  fore (i, 0, n)
    fore (j, 0, m)
      fx[i] = max(fx[i], a[i][j]);
  fore (i, 0, n) {
    vi t(m, -1), s(n + 1, i);
    for (p = q = 0; p <= q && x[i] < 0; p++)
      for (k = s[p], j = 0; j < m && x[i] < 0; j++)
        if (abs(fx[k] + fy[j] - a[k][j]) < eps && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if (s[q] < 0) for (p = j; p >= 0; j = p)
            y[j] = k = t[j], p = x[k], x[k] = j;
        }
    if (x[i] < 0) {
      C d = numeric_limits<C>::max();
      fore (k, 0, q + 1)
        fore (j, 0, m) if (t[j] < 0)
          d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      fore (j, 0, m)
        fy[j] += (t[j] < 0 ? 0 : d);
      fore (k, 0, q + 1)
        fx[s[k]] -= d;
      i--;
    } 
  }
  C cost = 0;
  fore (i, 0, n) cost += a[i][x[i]];
  return make_pair(cost, x);
}