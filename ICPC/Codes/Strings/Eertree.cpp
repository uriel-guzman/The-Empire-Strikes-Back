struct Eertree {
  struct Node : map<char, int> {
    int link = 0, len = 0;
  };

  vector<Node> trie;
  string s = "$";
  int last;

  Eertree() {
    last = newNode(), newNode();
    trie[0].link = 1, trie[1].len = -1;
  }

  int newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  int go(int u) {
    while (s[sz(s) - trie[u].len - 2] != s.back()) 
      u = trie[u].link;
    return u;
  }

  void extend(char c) {
    s += c;
    int u = go(last);
    if (!trie[u][c]) {
      int v = newNode();
      trie[v].len = trie[u].len + 2;
      trie[v].link = trie[go(trie[u].link)][c];
      trie[u][c] = v;
    }
    last = trie[u][c];
  }

  Node& operator [](int u) {
    return trie[u];
  }
};