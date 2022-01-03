struct Eertree {
  struct Node : map<char, int> {
    int link = 0, len = 0;
  };

  vector<Node> trie;
  string s = "$";
  int last;

  Eertree(int n = 1) {
    trie.reserve(n), last = newNode(), newNode();
    trie[0].link = 1, trie[1].len = -1;
  }

  int newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  int next(int u) {
    while (s[sz(s) - trie[u].len - 2] != s.back())
      u = trie[u].link;
    return u;
  }

  void extend(char c) {
    s.push_back(c);
    last = next(last);
    if (!trie[last][c]) {
      int v = newNode();
      trie[v].len = trie[last].len + 2;
      trie[v].link = trie[next(trie[last].link)][c];
      trie[last][c] = v;
    }
    last = trie[last][c];
  }

  Node& operator[](int u) {
    return trie[u];
  }

  void substringOccurrences() {
    fore (u, sz(s), 0)
      trie[trie[u].link].occ += trie[u].occ;
  }

  lli occurences(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return 0;
      u = trie[u][c];
    }
    return trie[u].occ;
  }
};