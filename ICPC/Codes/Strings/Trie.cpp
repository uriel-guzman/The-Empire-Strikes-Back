struct Trie {
  vector< map<char, int> > trie;
  vector<bool> isw;

  Trie() { newNode(); }

  int inline newNode() {
    trie.pb({}), isw.pb(false);
    return sz(trie) - 1;
  }

  void insert(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u][c])
        trie[u][c] = newNode();
      u = trie[u][c];
    }
    isw[u] = true;
  }

  bool find(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return false;
      u = trie[u][c];
    }
    return isw[u];
  }
};
