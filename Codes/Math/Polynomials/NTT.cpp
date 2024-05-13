template <const int G, const int M>
void NTT(vector<Modular<M>>& a, bool inv = false) {
  static vector<Modular<M>> root = {0, 1};
  static Modular<M> primitive(G);
  int n = sz(a);
  for (int i = 1, j = 0; i < n - 1; i++) {
    for (int k = n >> 1; (j ^= k) < k; k >>= 1);
    if (i < j)
      swap(a[i], a[j]);
  }
  int k = sz(root);
  if (k < n)
    for (root.resize(n); k < n; k <<= 1) {
      auto z = primitive.pow((M - 1) / (k << 1));
      fore (i, k >> 1, k) {
        root[i << 1] = root[i];
        root[i << 1 | 1] = root[i] * z;
      }
    }
  for (int k = 1; k < n; k <<= 1)
    for (int i = 0; i < n; i += k << 1)
      fore (j, 0, k) {
        auto t = a[i + j + k] * root[j + k];
        a[i + j + k] = a[i + j] - t;
        a[i + j] = a[i + j] + t;
      }
  if (inv) {
    reverse(1 + all(a));
    auto invN = Modular<M>(1) / n;
    for (auto& x : a) x = x * invN;
  }
}

template <int G = 3, const int M = 998244353>
vector<Modular<M>> convolution(vector<Modular<M>> a, vector<Modular<M>> b) {
  // find G using primitive(M)
  // Common NTT couple (3, 998244353)
  if (a.empty() || b.empty())
    return {};

  int n = sz(a) + sz(b) - 1, m = n;
  while (n != (n & -n)) ++n;
  a.resize(n, 0), b.resize(n, 0);

  NTT<G, M>(a), NTT<G, M>(b);
  fore (i, 0, n)
    a[i] = a[i] * b[i];
  NTT<G, M>(a, true);

  return a;
}