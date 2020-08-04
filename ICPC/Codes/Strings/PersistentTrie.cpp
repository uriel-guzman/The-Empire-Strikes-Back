struct PersistentTrie {
  vector< map<char, int> > trie;
  vector<bool> isw;
  vi root;

  PersistentTrie() { root.pb(newNode()); }

  int inline newNode() {
    trie.pb({}), isw.pb(0);
    return sz(trie) - 1;
  }

  void insert(string &s, ii u) {
    for (char c : s) {
      trie[u.s] = trie[u.f]; // copy all stuff from the previous version
      trie[u.s][c] = newNode();
      u.f = trie[u.f][c];
      u.s = trie[u.s][c];
      isw[u.s] = isw[u.f];
    }
    isw[u.s] = 1;
  }

  void insertFrom(string &s, int i) {
    root.pb(newNode());
    insert(s, make_pair(root[i], root.back()));
  }

  void dfs(int u, string &s) {
    if (isw[u])
      debug(s);
    for (auto [c, v] : trie[u]) {
      s.pb(c);
      dfs(v, s);
      s.pop_back();
    }
  }
} trie;