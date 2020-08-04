int z[N];

void zf(string &s) {
  for (int i = 1, l = 0, r = 0; i < sz(s); i++) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < sz(s) && s[i + z[i]] == s[z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
}