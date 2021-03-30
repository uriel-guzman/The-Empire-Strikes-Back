vector<int> virt[N];
 
int virtualTree(vector<int> &ver) {
  auto byDfs = [&](int u, int v) {
    return tin[u] < tin[v];
  };
  sort(all(ver), byDfs);
  fore (i, sz(ver), 1)
    ver.pb(lca(ver[i - 1], ver[i]));
  sort(all(ver), byDfs);
  ver.erase(unique(all(ver)), ver.end());
  for (int u : ver)
    virt[u].clear();
  fore (i, 1, sz(ver)) 
    virt[lca(ver[i - 1], ver[i])].pb(ver[i]);
  return ver[0];
}