vi p = {10006793, 1777771, 10101283, 10101823, 10136359, 10157387, 10166249};
vi mod = {999992867, 1070777777, 999727999, 1000008223, 1000009999, 1000003211, 1000027163, 1000002193, 1000000123};
int pw[2][N], ipw[2][N];

struct Range : array<lli, 2> {
  int l, r;
  Range(int l, int r) : l(l), r(r) { fill(0); }
};

struct Hash {
  vector<vi> h;
 
  Hash(string &s) : h(2, vi(sz(s) + 1, 0)) {
    fore (i, 0, 2) 
      fore (j, 0, sz(s)) {
        lli x = s[j] - 'a' + 1;
        h[i][j + 1] = (h[i][j] + x * pw[i][j]) % mod[i];
      }
  }
 
  Range cut(int l, int r) {
    Range f(l, r);
    fore (i, 0, 2) {
      f[i] = (h[i][r + 1] - h[i][l] + mod[i]) % mod[i];
      f[i] = f[i] * ipw[i][l] % mod[i];
    }
    return f;
  }
};

Range merge(vector<Range>& cuts) {
  Range g(-1, -1);
  fore (j, sz(cuts), 0) { // downward!!
    Range f = cuts[j];
    fore (i, 0, 2) {  
      f[i] += g[i] * pw[i][f.r - f.l + 1] % mod[i];
      f[i] %= mod[i];
    }
    swap(f, g);
  }
  return g;
}

shuffle(all(p), rng), shuffle(all(mod), rng);
fore (i, 0, 2) {
  ipw[i][0] = inv(pw[i][0] = 1LL, mod[i]);
  int q = inv(p[0], mod[i]);
  fore (j, 1, N) {
    pw[i][j] = 1LL * pw[i][j - 1] * p[0] % mod[i];
    ipw[i][j] = 1LL * ipw[i][j - 1] * q % mod[i];
  } 
}
