int go[N][A];

void kmpAutomaton(string &s) {
  s += "$";
  vi p = lps(s);
  fore (i, 0, sz(s))
    fore (c, 0, A) {
      if (i && s[i] != 'a' + c)
        go[i][c] = go[p[i - 1]][c];
      else
        go[i][c] = i + ('a' + c == s[i]);
    }
  s.pop_back();
}