struct AhoCorasick {
  struct Node : map<char, int> {
    int link = 0, up = 0;
    int cnt = 0, isWord = 0;
  };

  vector<Node> trie;

  AhoCorasick(int n = 1) {
    trie.reserve(n), newNode();
  }

  int newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  void insert(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u][c])
        trie[u][c] = newNode();
      u = trie[u][c];
    }
    trie[u].cnt++, trie[u].isWord = 1;
  }

  int next(int u, char c) {
    while (u && !trie[u].count(c))
      u = trie[u].link;
    return trie[u][c];
  }

  void pushLinks() {
    queue<int> qu;
    qu.push(0);
    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();
      for (auto& [c, v] : trie[u]) {
        int l = (trie[v].link = u ? next(trie[u].link, c) : 0);
        trie[v].cnt += trie[l].cnt;
        trie[v].up = trie[l].isWord ? l : trie[l].up;
        qu.push(v);
      }
    }
  }

  template <class F>
  void goUp(int u, F f) {
    for (; u != 0; u = trie[u].up)
      f(u);
  }

  int match(string& s, int u = 0) {
    int ans = 0;
    for (char c : s) {
      u = next(u, c);
      ans += trie[u].cnt;
    }
    return ans;
  }

  Node& operator[](int u) {
    return trie[u];
  }
};