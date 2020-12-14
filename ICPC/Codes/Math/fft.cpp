template <class Complex>
void fft(vector<Complex> &x, int inv) {
  int n = sz(x);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(x[i], x[j]);
  }
  vector<Complex> wp(n >> 1);
  for (int k = 1; k < n; k <<= 1) {
    fore (i, 0, k)
      wp[i] = polar(1.0, pi * i / k * inv);
    for (int i = 0; i < n; i += k << 1) 
      fore (j, 0, k) {
        Complex t = x[i + j + k] * wp[j];
        x[i + j + k] = x[i + j] - t; 
        x[i + j] = x[i + j] + t;
      }    
  }
  if (inv == -1) {
    fore (i, 0, n) x[i] /= n;
  }
}
 
template <class Complex>
vector<Complex> convolution(vector<Complex> a, vector<Complex> b) {
  int n = sz(a) + sz(b) - 1;
  int k = 1 << (1 + __lg(n)); // nearest power of two
  a.resize(k), b.resize(k);
  fft(a, +1), fft(b, +1);
  fore (i, 0, k)
    a[i] *= b[i];
  fft(a, -1), a.resize(n);
  return a;
}