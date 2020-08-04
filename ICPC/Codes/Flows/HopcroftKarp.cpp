struct HopcroftKarp {
  int n, m = 0;
  vector<vi> g;
  vi dist, match;
 
  HopcroftKarp(int _n) : n(5 + _n), g(n + 5), dist(n + 5), match(n + 5, 0) {}
 
  void add(int u, int v) {
    g[u].pb(v), g[v].pb(u);
    m += 2;
  }
 
  bool bfs() {
    queue<int> qu;
    fill(all(dist), -1);
    fore (u, 1, n + 1)  
      if (!match[u])
        dist[u] = 0, qu.push(u);
    while (!qu.empty()) {
      int u = qu.front(); qu.pop();
      for (int v : g[u]) 
        if (dist[match[v]] == -1) {
          dist[match[v]] = dist[u] + 1;
          if (match[v])
            qu.push(match[v]);
        }
    }
    return dist[0] != -1;
  }
 
  bool dfs(int u) {
    for (int v : g[u])
      if (!match[v] || (dist[u] + 1 == dist[match[v]] && dfs(match[v]))) {
        match[u] = v, match[v] = u;
        return 1;
      }
    dist[u] = 1 << 30;
    return 0;
  }
 
  int maxMatching() {
    int tot = 0;
    while (bfs())
      fore (u, 1, n + 1) 
        tot += match[u] ? 0 : dfs(u);
    return tot;
  }
};