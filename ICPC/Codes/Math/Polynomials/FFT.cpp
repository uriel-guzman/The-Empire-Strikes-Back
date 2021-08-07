template <class Complex>
void FFT(vector<Complex> &a, bool inv = false) {
  const static double PI = 4.0 * atan(1.0);
  int n = sz(a);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(a[i], a[j]);
  }
  vector<Complex> root(n / 2, 1);
  for (int k = 1; k < n; k <<= 1) {
    const double ang = PI / k;
    Complex ratio(cos(ang), sin(ang));
    if (inv) ratio = conj(ratio);
    fore (i, 1, k)
      root[i] = root[i - 1] * ratio;
    for (int i = 0; i < n; i += k << 1) 
      fore (j, 0, k) {
        Complex tmp = a[i + j + k] * root[j];
        a[i + j + k] = a[i + j] - tmp; 
        a[i + j] = a[i + j] + tmp;
      }
  }
}

template <class T>
vector<T> convolution(vector<T> &a, vector<T> &b) {
  if (a.empty() || b.empty()) return {};

  int n = sz(a) + sz(b) - 1, m = n;
  while (n != (n & -n)) ++n;
  
  vector<complex<double>> fa(n), fb(n);
  fore (i, 0, sz(a)) fa[i].real(a[i]);
  fore (i, 0, sz(b)) fb[i].real(b[i]);

  FFT(fa), FFT(fb);
  fore (i, 0, n)
    fa[i] *= fb[i];
  FFT(fa, true);

  vector<T> ans(m);
  fore (i, 0, m)  
    ans[i] = round(real(fa[i]) / n);
  return ans;
}