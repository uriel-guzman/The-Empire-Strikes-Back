lli fpow(lli x, lli y, lli mod) {
  lli r = 1;
  (y %= (mod - 1)) += mod - 1;
  for (; y > 0; y >>= 1) {
    if (y & 1) r = r * x % mod;
    x = x * x % mod;
  }
  return r;
}

template <int p, int g>
void ntt(vector<int> &x, int inv) {
  int n = x.size();
  for (int i = 1, j = 0; i < n - 1; ++i) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(x[i], x[j]);
  }
  vector<lli> wp(n >> 1, 1);
  for (int k = 1; k < n; k <<= 1) {
    lli wk = fpow(g, inv * (p - 1) / (k << 1), p); 
    fore(i, 1, k) 
      wp[i] = wp[i - 1] * wk % p;
    for (int i = 0; i < n; i += k << 1) 
      fore(j, 0, k) {
        int u = x[i + j], v = x[i + j + k] * wp[j] % p;
        x[i + j] = (u + v + p) % p;
        x[i + j + k] = (u - v + p) % p;
      }
  }
  if (inv == -1) {
    lli m = fpow(n, p - 2, p); // m = inv(n)
    fore(i, 0, n) x[i] = x[i] * m % p;
  }
}

template <int p = 7340033, int g = 3>
vector<int> convolution(vector<int> a, vector<int> b) {
  int n = sz(a) + sz(b) - 1;
  int k = 1 << (1 + __lg(n)); // nearest power of two
  a.resize(k), b.resize(k);
  ntt<p, g>(a, 1), ntt<p, g>(b, 1);
  fore (i, 0, k)
    a[i] = 1LL * a[i] * b[i] % p;
  ntt<p, g>(a, -1), a.resize(n);
  return a;
}