template <class F>
struct Dinic {
  struct Edge {
    int v, inv;
    F cap, flow;
    Edge(int v, F cap, int inv) : v(v), cap(cap), flow(0), inv(inv) {}
  };
 
  F eps = (F) 1e-9;
  int s, t, n;
  vector<vector<Edge>> graph;
  vector<int> dist, ptr;
 
  Dinic(int n) : n(n), graph(n), dist(n), ptr(n), s(n - 2), t(n - 1) {}
 
  void add(int u, int v, F cap) {
    graph[u].pb(Edge(v, cap, sz(graph[v])));
    graph[v].pb(Edge(u, 0, sz(graph[u]) - 1));
  }
 
  bool bfs() {
    fill(all(dist), -1);
    queue<int> qu({s});
    dist[s] = 0;
    while (sz(qu) && dist[t] == -1) {
      int u = qu.front(); 
      qu.pop();
      for (Edge &e : graph[u]) if (dist[e.v] == -1) 
        if (e.cap - e.flow > eps) {
          dist[e.v] = dist[u] + 1;
          qu.push(e.v);
        } 
    }
    return dist[t] != -1;
  }
 
  F dfs(int u, F flow = numeric_limits<F>::max()) {
    if (flow <= eps || u == t)
      return max<F>(0, flow);
    for (int &i = ptr[u]; i < sz(graph[u]); i++) {
      Edge &e = graph[u][i];
      if (e.cap - e.flow > eps && dist[u] + 1 == dist[e.v]) {
       F pushed = dfs(e.v, min<F>(flow, e.cap - e.flow));
        if (pushed > eps) {
          e.flow += pushed;
          graph[e.v][e.inv].flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }
 
  F maxFlow() {
    F flow = 0;
    while (bfs()) {
      fill(all(ptr), 0);
      while (F pushed = dfs(s)) 
        flow += pushed;
    }
    return flow;
  }
};