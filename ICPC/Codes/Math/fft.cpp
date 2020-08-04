template <class C>
void fft(vector<C> &x, int inv) {
  int n = sz(x);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(x[i], x[j]);
  }
  vector<C> wp(n >> 1);
  for (int len = 1; len < n; len <<= 1) {
    fore (i, 0, len)
      wp[i] = polar(1.0, pi * i / len * inv);
    for (int i = 0; i < n; i += len << 1) 
      fore (j, 0, len) {
        C t = x[i + j + len] * wp[j];
        x[i + j + len] = x[i + j] - t; 
        x[i + j] += t;
      }    
  }
  if (inv == -1)
    fore (i, 0, n)
      x[i] /= n;
}
 
template <class C>
void convolution(vector<C> &a, vector<C> &b) {
  int n = sz(a) + sz(b) - 1, k = 1;
  while (k < n) k <<= 1;
  a.resize(k), b.resize(k);
  fft(a, +1), fft(b, +1);
  fore (i, 0, k)
    a[i] *= b[i];
  fft(a, -1);
}