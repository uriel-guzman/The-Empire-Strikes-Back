int pal[2][N];

void manacher(string &s) {
  fore (k, 0, 2) {
    int l = 0, r = 0;
    fore (i, 0, sz(s)) {
      if (i < r)
        pal[k][i] = min(r - i + !k, pal[k][l + r - i + !k]);
      int p = i - pal[k][i], q = i + pal[k][i] - !k;
      while (p >= 1 && q + 1 < sz(s) && s[p - 1] == s[q + 1]) 
        ++pal[k][i], --p, ++q;
      if (q > r)  
        l = p, r = q;
    }
  }
}