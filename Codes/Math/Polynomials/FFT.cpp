template <class Complex>
void FFT(vector<Complex>& a, bool inv = false) {
  const static double PI = acos(-1.0);
  static vector<Complex> root = {0, 1};
  int n = sz(a);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(a[i], a[j]);
  }
  int k = sz(root);
  if (k < n)
    for (root.resize(n); k < n; k <<= 1) {
      Complex z(cos(PI / k), sin(PI / k));
      fore (i, k >> 1, k) {
        root[i << 1] = root[i];
        root[i << 1 | 1] = root[i] * z;
      }
    }
  for (int k = 1; k < n; k <<= 1)
    for (int i = 0; i < n; i += k << 1)
      fore (j, 0, k) {
        Complex t = a[i + j + k] * root[j + k];
        a[i + j + k] = a[i + j] - t;
        a[i + j] = a[i + j] + t;
      }
  if (inv) {
    reverse(1 + all(a));
    for (auto& x : a) x /= n;
  }
}

template <class T>
vector<T> convolution(const vector<T>& a, const vector<T>& b) {
  if (a.empty() || b.empty()) return {};

  int n = sz(a) + sz(b) - 1, m = n;
  while (n != (n & -n)) ++n;

  vector<complex<double>> fa(all(a)), fb(all(b));
  fa.resize(n), fb.resize(n);
  FFT(fa, false), FFT(fb, false);
  fore (i, 0, n) fa[i] *= fb[i];
  FFT(fa, true);

  vector<T> ans(m);
  fore (i, 0, m) ans[i] = round(real(fa[i]));
  return ans;
}

template <class T>
vector<T> convolutionTrick(const vector<T>& a,
                           const vector<T>& b) { // 2 FFT's instead of 3!!
  if (a.empty() || b.empty()) return {};

  int n = sz(a) + sz(b) - 1, m = n;
  while (n != (n & -n)) ++n;

  vector<complex<double>> in(n), out(n);
  fore (i, 0, sz(a)) in[i].real(a[i]);
  fore (i, 0, sz(b)) in[i].imag(b[i]);

  FFT(in, false);
  for (auto& x : in) x *= x;
  fore (i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
  FFT(out, false);

  vector<T> ans(m);
  fore (i, 0, m) ans[i] = round(imag(out[i]) / (4 * n));
  return ans;
}