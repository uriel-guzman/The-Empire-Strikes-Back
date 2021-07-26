template <class T>
vector<int> lps(T s) {
  vector<int> p(sz(s), 0);
  for (int j = 0, i = 1; i < sz(s); i++) {
    while (j && s[i] != s[j]) j = p[j - 1];
    if (s[i] == s[j]) j++;
    p[i] = j;
  }
  return p;
}

// positions where t is on s
template <class T>
vector<int> kmp(T &s, T &t) { 
  vector<int> p = lps(t), pos;
  for (int j = 0, i = 0; i < sz(s); i++) {
    while (j && s[i] != t[j]) j = p[j - 1];
    if (s[i] == t[j]) j++;
    if (j == sz(t)) pos.pb(i - sz(t) + 1);
  }
  return pos;
}