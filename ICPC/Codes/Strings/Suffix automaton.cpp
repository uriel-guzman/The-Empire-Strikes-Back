struct SuffixAutomaton {
  struct Node : map<char, int> {
    int link = -1, len = 0;
  };

  vector<Node> trie;
  int last;

  SuffixAutomaton(int n = 1) {
    trie.reserve(2 * n), last = newNode();
  }

  int newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  void extend(char c) {
    int u = newNode();
    trie[u].len = trie[last].len + 1;
    int p = last;
    while (p != -1 && !trie[p].count(c)) {
      trie[p][c] = u;
      p = trie[p].link;
    }
    if (p == -1)
      trie[u].link = 0;
    else {
      int q = trie[p][c];
      if (trie[p].len + 1 == trie[q].len)
        trie[u].link = q;
      else {
        int clone = newNode();
        trie[clone] = trie[q];
        trie[clone].len = trie[p].len + 1;
        while (p != -1 && trie[p][c] == q) {
          trie[p][c] = clone;
          p = trie[p].link;
        }
        trie[q].link = trie[u].link = clone;
      }
    }
    last = u;
  }

  string kthSubstring(lli kth, int u = 0) {
    // number of different substrings (dp)
    string s = "";
    while (kth > 0)
      for (auto& [c, v] : trie[u]) {
        if (kth <= diff(v)) {
          s.pb(c), kth--, u = v;
          break;
        }
        kth -= diff(v);
      }
    return s;
  }

  void substringOccurrences() {
    // trie[u].occ = 1, trie[clone].occ = 0
    vector<int> who(sz(trie) - 1);
    iota(all(who), 1);
    sort(all(who), [&](int u, int v) {
      return trie[u].len > trie[v].len;
    });
    for (int u : who) {
      int l = trie[u].link;
      trie[l].occ += trie[u].occ;
    }
  }

  lli occurences(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return 0;
      u = trie[u][c];
    }
    return trie[u].occ;
  }

  int longestCommonSubstring(string& s, int u = 0) {
    int mx = 0, len = 0;
    for (char c : s) {
      while (u && !trie[u].count(c)) {
        u = trie[u].link;
        len = trie[u].len;
      }
      if (trie[u].count(c))
        u = trie[u][c], len++;
      mx = max(mx, len);
    }
    return mx;
  }

  string smallestCyclicShift(int n, int u = 0) {
    string s = "";
    fore (i, 0, n) {
      char c = trie[u].begin()->f;
      s += c;
      u = trie[u][c];
    }
    return s;
  }

  int leftmost(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return -1;
      u = trie[u][c];
    }
    return trie[u].pos - sz(s) + 1;
  }

  Node& operator[](int u) {
    return trie[u];
  }
};