template <class F>
struct Dinic {
  struct Edge {
    int v, inv;
    F cap, flow;
    Edge(int v, F cap, int inv) : 
      v(v), cap(cap), flow(0), inv(inv){}
  };
 
  F eps = (F) 1e-9, lim = (F) 1e-9;
  const bool scaling = 0;
  int s, t, n, m = 0;
  vector< vector<Edge> > g;
  vi dist, ptr;
 
  Dinic(int n, int ss = -1, int tt = -1) : 
    n(n), g(n + 5), dist(n + 5), ptr(n + 5) {
    s = ss == -1 ? n + 1 : ss;
    t = tt == -1 ? n + 2 : tt;
  }
 
  void add(int u, int v, F cap) {
    g[u].pb(Edge(v, cap, sz(g[v])));
    g[v].pb(Edge(u, 0, sz(g[u]) - 1));
    lim = (scaling ? max(lim, cap) : lim);
    m += 2;
  }
 
  bool bfs() {
    fill(all(dist), -1);
    queue<int> qu({s});
    dist[s] = 0;
    while (sz(qu) && dist[t] == -1) {
      int u = qu.front(); qu.pop();
      for (Edge &e : g[u]) if (dist[e.v] == -1) 
        if (scaling ? e.cap - e.flow >= lim : e.cap - e.flow > eps) {
          dist[e.v] = dist[u] + 1;
          qu.push(e.v);
        } 
    }
    return dist[t] != -1;
  }
 
  F dfs(int u, F flow = numeric_limits<F>::max()) {
    if (flow <= eps || u == t)
      return max<F>(0, flow);
    for (int &i = ptr[u]; i < sz(g[u]); i++) {
      Edge &e = g[u][i];
      if (e.cap - e.flow > eps && dist[u] + 1 == dist[e.v]) {
       F pushed = dfs(e.v, min<F>(flow, e.cap - e.flow));
        if (pushed > eps) {
          e.flow += pushed;
          g[e.v][e.inv].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }
 
  F maxFlow() {
    F flow = 0;
    for (lim = scaling ? lim : 1; lim > eps; lim /= 2)
      while (bfs()) {
        fill(all(ptr), 0);
        while (F pushed = dfs(s)) 
          flow += pushed;
      }
    return flow;
  }
};