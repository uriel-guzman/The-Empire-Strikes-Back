struct HopcroftKarp {
  int n, m;
  vector<vector<int>> graph;
  vector<int> dist, match;

  HopcroftKarp(int k) : n(k + 1), graph(n), dist(n), 
                        match(n, 0) {} // 1-indexed!!

  void add(int u, int v) { 
    graph[u].pb(v), graph[v].pb(u); 
  }

  bool bfs() {
    queue<int> qu;
    fill(all(dist), -1);
    fore (u, 1, n)
      if (!match[u]) dist[u] = 0, qu.push(u);
    while (!qu.empty()) {
      int u = qu.front();
      qu.pop();
      for (int v : graph[u])
        if (dist[match[v]] == -1) {
          dist[match[v]] = dist[u] + 1;
          if (match[v]) qu.push(match[v]);
        }
    }
    return dist[0] != -1;
  }

  bool dfs(int u) {
    for (int v : graph[u])
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
      fore (u, 1, n) tot += match[u] ? 0 : dfs(u);
    return tot;
  }
};