int lo[Q], hi[Q];
queue<int> solve[N];
vector<Query> queries;

fore (it, 0, 1 + __lg(N)) { 
  fore (i, 0, sz(queries))
    if (lo[i] != hi[i]) {
      int mid = (lo[i] + hi[i]) / 2;
      solve[mid].emplace(i);
    }
  fore (x, 0, n) {
    // simulate
    while (!solve[x].empty()) {
      int i = solve[x].front();
      solve[x].pop();
      if (can(queries[i])) 
        hi[i] = x;
      else
        lo[i] = x + 1;
    }
  }
}