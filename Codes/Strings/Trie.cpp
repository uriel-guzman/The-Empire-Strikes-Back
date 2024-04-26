struct Trie {
  struct Node : map<char, int> {
    bool isWord = false;
  };

  vector<Node> trie;

  Trie(int n = 1) { trie.reserve(n), newNode(); }

  int inline newNode() {
    trie.pb({});
    return sz(trie) - 1;
  }

  void insert(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u][c]) trie[u][c] = newNode();
      u = trie[u][c];
    }
    trie[u].isWord = true;
  }

  bool find(string& s, int u = 0) {
    for (char c : s) {
      if (!trie[u].count(c)) return false;
      u = trie[u][c];
    }
    return trie[u].isWord;
  }

  Node& operator[](int u) { return trie[u]; }
};