int lps[N];

void pre(string &s) {
  int j = (lps[0] = 0);
  fore (i, 1, sz(s)) {
    while (j && s[i] != s[j])
      j = lps[j - 1];
    if (s[i] == s[j])
      j++;
    lps[i] = j;
  }
}
// how many times t occurs in s
int kmp(string &s, string &t) { 
  pre(t);
  int j = 0, tot = 0;
  fore (i, 0, sz(s)) {
    while (j && s[i] != t[j])
      j = lps[j - 1];
    if (s[i] == t[j])
      j++;
    if (j == sz(t))
      tot++; // pos: i - sz(t) + 1;
  }
  return tot;
}