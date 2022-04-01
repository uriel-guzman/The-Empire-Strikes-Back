int lo[QUERIES], hi[QUERIES];
queue<int> solve[UPDATES];
vector<Update> updates;
vector<Query> queries;

fore (it, 0, 1 + __lg(UPDATES)) {
  fore (i, 0, sz(queries))
    if (lo[i] != hi[i]) {
      int mid = (lo[i] + hi[i]) / 2;
      solve[mid].emplace(i);
    }
  fore (i, 0, sz(updates)) {
    // add the i-th update, we have a prefix of updates
    while (!solve[i].empty()) {
      int qi = solve[i].front();
      solve[i].pop();
      if (can(queries[qi]))
        hi[qi] = i;
      else
        lo[qi] = i + 1;
    }
  }
}