const int N = 2e5 + 5;
using Hash = int;
Hash pw[N];
		 
template <class T>
struct Hashing {
  static constexpr int P = 10166249, M = 1070777777;
  vector<Hash> h;
		 
  static void init() {
    pw[0] = 1;
    fore (i, 1, N)
      pw[i] = 1LL * pw[i - 1] * P % M;
  }

  Hashing(T& b, T& e) : h(r - l + 1) {
    int i = 0;
    for (auto it = b; it != e; it++) {
      lli x = *it - 'a' + 1;
      h[++i] = (1LL * h[i - 1] * P % M + x) % M;
    }
  }
		 
  Hashing(T& s) : Hashing(all(s)) {}

  Hash query(int l, int r) {
    return (h[r + 1] - 1LL * h[l] * pw[r - l + 1] % M + M) % M;
  }

  Hash full() {
    return h.back();
  }
};
		 
