template <int G, int M>
void NTT(vector<Modular<M>> &a, bool inv = false) {
  int n = sz(a);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j) swap(a[i], a[j]);
  }
  vector<Modular<M>> root(n / 2, 1);
  for (int k = 1; k < n; k <<= 1) {
    Modular<M> ratio = fpow<Modular<M>>(G, (M - 1) / (k << 1)); 
    if (inv) ratio = ratio.inv();
    fore (i, 1, k)
      root[i] = root[i - 1] * ratio;
    for (int i = 0; i < n; i += k << 1) 
      fore (j, 0, k) {
        Modular<M> tmp = a[i + j + k] * root[j];
        a[i + j + k] = a[i + j] - tmp; 
        a[i + j] = a[i + j] + tmp;
      }
  }
}

template <int G = 3, int M = 998244353>
vector<Modular<M>> convolution(vector<Modular<M>> a, vector<Modular<M>> b) {
  if (a.empty() || b.empty()) return {};

  int n = sz(a) + sz(b) - 1, m = n;
  while (n != (n & -n)) ++n;
  a.resize(n, 0), b.resize(n, 0);

  NTT<G, M>(a), NTT<G, M>(b);
  Modular<M> invN = Modular<M>(n).inv();    
  fore (i, 0, n)
    a[i] = a[i] * b[i] * invN;
  NTT<G, M>(a, true);
  
  return a.resize(m), a;
}