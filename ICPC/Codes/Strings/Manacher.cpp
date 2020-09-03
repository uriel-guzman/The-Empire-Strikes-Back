vector<vi> manacher(string &s) {
  vector<vi> pal(2, vi(sz(s), 0));
  fore (k, 0, 2) {
    int l = 0, r = 0;
    fore (i, 0, sz(s)) {
      int t = r - i + !k;
      if (i < r)
        pal[k][i] = min(t, pal[k][l + t]);
      int p = i - pal[k][i], q = i + pal[k][i] - !k;
      while (p >= 1 && q + 1 < sz(s) && s[p - 1] == s[q + 1]) 
        ++pal[k][i], --p, ++q;
      if (q > r)  
        l = p, r = q;
    }
  }
  return pal;
}