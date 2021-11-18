template <class T, int ALPHA = 26>
struct KmpAutomaton : vector<vector<int>> {
  KmpAutomaton() {}
  KmpAutomaton(T s) : vector<vector<int>>(sz(s) + 1, vector<int>(ALPHA)) {
    s.pb(0);
    vector<int> p = lps(s);
    auto& nxt = *this;
    nxt[0][s[0] - 'a'] = 1;
    fore (i, 1, sz(s))
      fore (c, 0, ALPHA)
        nxt[i][c] = (s[i] - 'a' == c ? i + 1 : nxt[p[i - 1]][c]);
  }
};