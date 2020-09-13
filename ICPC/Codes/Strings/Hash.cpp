vi p = {10006793, 1777771, 10101283, 10101823, 10136359, 10157387, 10166249};
vi mod = {999992867, 1070777777, 999727999, 1000008223, 1000009999, 1000003211, 1000027163, 1000002193, 1000000123};

struct Hash {
  vector<vi> h;
 
  Hash(string &s) : h(2, vi(sz(s) + 1, 0)) {
    fore (i, 0, 2) 
      fore (j, 0, sz(s)) {
        lli x = s[j] - 'a' + 1;
        h[i][j + 1] = (h[i][j] + x * fpow(p[0], j, mod[i])) % mod[i];
      }
  }
 
  array<lli, 2> cut(int l, int r) {
    array<lli, 2> f;
    fore (i, 0, 2) {
      f[i] = (h[i][r + 1] - h[i][l] + mod[i]) % mod[i];
      f[i] = f[i] * inv(fpow(p[0], l, mod[i]), mod[i]) % mod[i];
    }
    return f;
  }

  array<lli, 2> query() { 
    return {0, 0}; 
  }

  template <class... Range>
  array<lli, 2> query(int l, int r, Range&&... rge) {
    array<lli, 2> f = cut(l, r);
    array<lli, 2> g = query(rge...);
    fore (i, 0, 2) {
      f[i] += g[i] * fpow(p[0], r - l + 1, mod[i]) % mod[i];
      f[i] %= mod[i];
    }
    return f;
  } 
};

shuffle(all(p), rng), shuffle(all(mod), rng);
