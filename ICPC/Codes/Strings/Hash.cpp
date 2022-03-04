using Hash = int; // maybe an arrray<int, 2>
Hash pw[N], ipw[N];

struct Hashing {
  static constexpr int P = 10166249, M = 1070777777;
  vector<Hash> h;

  static void init() {
    const int Q = inv(P, M);
    pw[0] = ipw[0] = 1;
    fore (i, 1, N) {
      pw[i] = 1LL * pw[i - 1] * P % M;
      ipw[i] = 1LL * ipw[i - 1] * Q % M;
    }
  }

  Hashing(string& s) : h(sz(s) + 1, 0) {
    fore (i, 0, sz(s)) {
      lli x = s[i] - 'a' + 1;
      h[i + 1] = (h[i] + x * pw[i]) % M;
    }
  }

  Hash query(int l, int r) {
    return 1LL * (h[r + 1] - h[l] + M) * ipw[l] % M;
  }

  static pair<Hash, int> merge(vector<pair<Hash, int>>& cuts) {
    pair<Hash, int> ans = {0, 0};
    fore (i, sz(cuts), 0) {
      ans.f = (cuts[i].f + 1LL * ans.f * pw[cuts[i].s] % M) % M;
      ans.s += cuts[i].s;
    }
    return ans;
  }
};