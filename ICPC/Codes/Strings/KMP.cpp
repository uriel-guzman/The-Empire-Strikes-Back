vi lps(string &s) {
  vi p(sz(s), 0);
  int j = 0;
  fore (i, 1, sz(s)) {
    while (j && s[i] != s[j])
      j = p[j - 1];
    j += (s[i] == s[j]);
    p[i] = j;
  }
  return p;
}
// how many times t occurs in s
int kmp(string &s, string &t) { 
  vi p = lps(t);
  int j = 0, tot = 0;
  fore (i, 0, sz(s)) {
    while (j && s[i] != t[j])
      j = p[j - 1];
    if (s[i] == t[j])
      j++;
    if (j == sz(t))
      tot++; // pos: i - sz(t) + 1;
  }
  return tot;
}