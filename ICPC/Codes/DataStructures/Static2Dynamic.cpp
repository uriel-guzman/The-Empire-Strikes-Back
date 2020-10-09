template <class Black, class T>
struct StaticDynamic {
  vector<Black> box;
  vector<vector<T>> st;

  explicit StaticDynamic(int n) box(1 + __lg(n)), st(1 + __lg(n)) {}

  void insert(T &x) {
    int p = 0;
    fore (i, 0, sz(st)) 
      if (st[i].empty()) {
        p = i;
        break;
      }
    st[p].pb(x);
    fore (i, 0, p) {
      st[p].insert(st[p].end(), all(st[i]));
      box[i].clear(), st[i].clear();
    }
    for (auto y : st[p])
      box[p].insert(y);
    box[p].init();
  }
};

