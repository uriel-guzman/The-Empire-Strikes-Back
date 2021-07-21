template <class C, class F>
struct Mcmf {
  struct Edge {
    int u, v, inv;
    F cap, flow;
    C cost;
    Edge(int u, int v, C cost, F cap, int inv) : u(u), v(v), cost(cost), cap(cap), flow(0), inv(inv) {}
  };

  F eps = (F) 1e-9;
  int s, t, n;
  vector<vector<Edge>> graph;
  vector<Edge*> prev;
  vector<C> cost, pot;
  
  Mcmf(int n) : n(n), graph(n), cost(n), pot(n, 0), prev(n), s(n - 2), t(n - 1) {} 

  void add(int u, int v, C cost, F cap) {
    graph[u].pb(Edge(u, v, cost, cap, sz(graph[v])));
    graph[v].pb(Edge(v, u, -cost, 0, sz(graph[u]) - 1));
  }

  bool dijkstra() {
    fill(all(cost), numeric_limits<C>::max());
    priority_queue<pair<C, int>, vector<pair<C, int>>, greater<pair<C, int>>> pq;
    pq.emplace(cost[s] = 0, s);
    while (sz(pq)) {
      C c = pq.top().f;
      int u = pq.top().s; 
      pq.pop();
      if (c != cost[u])
        continue;
      for (Edge &e : graph[u]) if (e.cap - e.flow > eps)
        if (cost[u] + e.cost + pot[u] - pot[e.v] < cost[e.v]) {
          cost[e.v] = cost[u] + e.cost + pot[u] - pot[e.v];
          prev[e.v] = &e;
          pq.emplace(cost[e.v], e.v);
        }
    }
    fore (u, 0, n) if (cost[u] < numeric_limits<C>::max())
      pot[u] += cost[u];
    return cost[t] != numeric_limits<C>::max();
  }

  pair<C, F> minCostFlow() {
    C cost = 0; F flow = 0;
    while (dijkstra()) {
      F pushed = numeric_limits<F>::max();
      for (Edge* e = prev[t]; e != nullptr; e = prev[e->u])
        pushed = min(pushed, e->cap - e->flow);
      for (Edge* e = prev[t]; e != nullptr; e = prev[e->u]) {
        e->flow += pushed;
        graph[e->v][e->inv].flow -= pushed;
        cost += e->cost * pushed;
      }
      flow += pushed;
    }
    return make_pair(cost, flow);
  }
};