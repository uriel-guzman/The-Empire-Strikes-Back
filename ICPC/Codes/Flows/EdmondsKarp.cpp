template <class F>
struct EdmondsKarp {
  vector< vector<int> > g;
  vector< vector<F> > cap;
  vector<int> path;
  vector<F> flow;
  int s, t, n, m = 0;

  EdmondsKarp(int n, int ss = -1, int tt = -1) : 
    n(n), g(n + 5), cap(n + 5, vector<F>(n + 5)), path(n + 5), flow(n + 5) {
    s = ss == -1 ? n + 1: ss;
    t = tt == -1 ? n + 2: tt;
  }

  void add(int u, int v, F ncap) {
    g[u].pb(v), g[v].pb(u);
    cap[u][v] = cap[v][u] = ncap;
  }

  F bfs() {
    fill(all(path), -1);
    fill(all(flow), 0);
    queue<int> qu;
    qu.push(s);
    flow[s] = numeric_limits<F>::max() / 2;
    while (!qu.empty()) {
      int u = qu.front(); qu.pop();
      for (int v : g[u])
        if (path[v] == -1 && cap[u][v] > 0) {
          path[v] = u;
          flow[v] = min(flow[u], cap[u][v]);
          if (v == t)
            return flow[v];
          qu.push(v);
        }
    }
    return 0;
  }

  F maxFlow() {
    F flow = 0;
    while (F nflow = bfs()) {
      flow += nflow;
      for (int u, v = t; v != s; v = u) {
        u = path[v];
        cap[u][v] -= nflow, cap[v][u] += nflow;
      }
    }
    return flow;
  }

  void minCut(){
    fore (u, 1, n) if (flow[u])
      for (int v: g[u])
        if (!flow[v] && mem[u][v])
          // cut edge u -> v
  }
};
