template <class Black, class T>
struct StaticDynamic {
  Black box[25];
  vector<T> st[25];

  void insert(T& x) {
    int p = 0;
    while (p < 25 && !st[p].empty()) p++;
    st[p].pb(x);
    fore (i, 0, p) {
      st[p].insert(st[p].end(), all(st[i]));
      box[i].clear(), st[i].clear();
    }
    for (auto y : st[p]) box[p].insert(y);
    box[p].init();
  }
};
