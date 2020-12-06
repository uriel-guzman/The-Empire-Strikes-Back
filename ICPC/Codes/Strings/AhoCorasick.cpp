struct AhoCorasick {
  struct Node : map<char, int> {
    int link = 0, cnt = 0;
  };
  vector<Node> trie;

  AhoCorasick() { newNode(); }

  int newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  void insert(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u][c])
        trie[u][c] = newNode();
      u = trie[u][c];
    }
    trie[u].cnt++;
  }

  int go(int u, char c) {
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
      for (auto &[c, v] : trie[u]) {
        int l = (trie[v].link = u ? go(trie[u].link, c) : 0);
        trie[v].cnt += trie[l].cnt;
        qu.push(v);
      }
    }
  }

  int match(string &s, int u = 0) {
    int ans = 0;
    for (char c : s)
      u = go(u, c), ans += trie[u].cnt;
    return ans;
  }
};