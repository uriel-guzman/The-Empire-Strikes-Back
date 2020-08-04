struct Eertree {
  vector< map<char, int> > trie;
  vi link, len;
  string s = "$";
  int last;

  Eertree() {
    last = newNode(), newNode();
    link[0] = 1, len[1] = -1;
  }

  int newNode() {
    trie.pb({}), link.pb(0), len.pb(0);
    return sz(trie) - 1;
  }

  int go(int u) {
    while (s[sz(s) - len[u] - 2] != s.back()) 
      u = link[u];
    return u;
  }

  void extend(char c) {
    s += c;
    int u = go(last);
    if (!trie[u][c]) {
      int v = newNode();
      len[v] = len[u] + 2;
      link[v] = trie[go(link[u])][c];
      trie[u][c] = v;
    }
    last = trie[u][c];
  }
} eert;