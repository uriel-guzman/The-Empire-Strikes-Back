vi virt[N];
 
int virtualTree(vi &ver) {
  auto byDfs = [&](int u, int v) {
    return tin[u] < tin[v];
  };
 
  sort(all(ver), byDfs);
  int k = sz(ver);
  fore (i, 1, k)
    ver.pb(lca(ver[i - 1], ver[i]));
  sort(all(ver), byDfs);
  ver.erase(unique(all(ver)), ver.end());
  for (int u : ver)
    virt[u].clear();
 
  auto above = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  };
 
  vi stk = {ver[0]};
  fore (i, 1, sz(ver)) {
    int u = ver[i];
    while (sz(stk) >= 2 && !above(stk.back(), u)) {
      virt[stk.end()[-2]].pb(stk.back());
      stk.pop_back();
    }
    stk.pb(u);
  }
  while (sz(stk) >= 2) {
    virt[stk.end()[-2]].pb(stk.back());
    stk.pop_back();
  }
 
  return stk[0];
}