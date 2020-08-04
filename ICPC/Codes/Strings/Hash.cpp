vi p = {10006793, 1777771, 10101283, 10101823, 10136359, 10157387, 10166249};
vi mod = {999992867, 1070777777, 999727999, 1000008223, 1000009999, 1000003211, 1000027163, 1000002193, 1000000123};
int pw[2][N];
 
struct Hash {
  vector<vi> h;
 
  Hash(string &s) : h(2, vi(sz(s) + 1, 0)) {
    fore (i, 0, 2) 
      fore (j, 0, sz(s))
        h[i][j + 1] = (h[i][j] + lli(s[j] - 'a' + 1) * pw[i][j]) % mod[i];
  }
 
  lli query(int l, int r) {
    lli f[2] = {0, 0};
    fore (i, 0, 2) 
      f[i] = 1LL * (h[i][r + 1] - h[i][l] + mod[i]) % mod[i] * pw[i][N - l - 1] % mod[i];
    return (f[0] << 32) | f[1];
  }
};

shuffle(all(p), rng), shuffle(all(mod), rng);
fore (i, 0, 2) {
  pw[i][0] = 1LL;
  fore (j, 1, N)
    pw[i][j] = 1LL * p[0] * pw[i][j - 1] % mod[i];
}