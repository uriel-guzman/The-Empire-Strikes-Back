struct AhoCorasick {
  vector< map<char, int> > trie;
  vi link, cnt;

  AhoCorasick() { newNode(); }

  int newNode() {
    trie.pb({}), link.pb(0), cnt.pb(0);
    return sz(trie) - 1;
  }

  void insert(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u][c])
        trie[u][c] = newNode();
      u = trie[u][c];
    }
    cnt[u]++;
  }

  int go(int u, char c) {
    while (u && !trie[u].count(c))
      u = link[u];
    return trie[u][c];
  }

  void pushLinks() {
    queue<int> qu;
    qu.push(0);
    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();
      for (auto &[c, v] : trie[u]) {
        if (v == 0) {
          v = trie[link[u]][c];
          continue;
        }
        link[v] = u ? go(link[u], c) : 0;
        cnt[v] += cnt[link[v]];
        qu.push(v);
      }
    }
  }

  int match(string &s, int u = 0) {
    int ans = 0;
    for (char c : s)
      u = go(u, c), ans += cnt[u];
    return ans;
  }
};