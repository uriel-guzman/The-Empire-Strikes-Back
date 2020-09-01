struct SuffixAutomaton {
  vector< map<char, int> > trie;
  vi link, len;
  int last;

  SuffixAutomaton() { last = newNode(); }

  int newNode() {
    trie.pb({}), link.pb(-1), len.pb(0);
    return sz(trie) - 1;
  }

  void extend(char c) {
    int u = newNode();
    len[u] = len[last] + 1;
    int p = last;
    while (p != -1 && !trie[p].count(c)) {
      trie[p][c] = u;
      p = link[p];
    }
    if (p == -1)
      link[u] = 0;
    else {
      int q = trie[p][c];
      if (len[p] + 1 == len[q])
        link[u] = q;
      else {
        int clone = newNode();
        len[clone] = len[p] + 1;
        trie[clone] = trie[q];
        link[clone] = link[q];
        while (p != -1 && trie[p][c] == q) {
          trie[p][c] = clone;
          p = link[p];
        }
        link[q] = link[u] = clone;
      }
    }
    last = u;
  }

  string qkthSubstring(lli kth, int u = 0) {
    // number of different substrings (dp)
    string s = "";
    while (kth > 0)
      for (auto &[c, v] : trie[u]) {
        if (kth <= diff(v)) {
          s.pb(c), kth--, u = v;
          break;
        }
        kth -= diff(v);
      }
    return s;
  }

  void occurs() {
    // occ[u] = 1, occ[clone] = 0
    vi who;
    fore (u, 1, sz(trie))
      who.pb(u);
    sort(all(who), [&](int u, int v) {
      return len[u] > len[v];
    });
    for (int u : who)
      occ[link[u]] += occ[u];
  }

  int qocc(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return 0;
      u = trie[u][c];
    }
    return occ[u];
  }

  int longestCommonSubstring(string &s, int u = 0) {
    int mx = 0, clen = 0;
    for (char c : s) {
      while (u && !trie[u].count(c)) {
        u = link[u];
        clen = len[u];
      }
      if (trie[u].count(c))
        u = trie[u][c], clen++;
      mx = max(mx, clen);
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

  int leftmost(string &s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c))
        return -1;
      u = trie[u][c];
    }
    return pos[u] - sz(s) + 1;
  }
};
