template <class C, class F>
struct Mcmf {
  struct Edge {
    int u, v, inv;
    F cap, flow;
    C cost;
    Edge(int u, int v, C cost, F cap, int inv) : u(u), v(v), cost(cost), cap(cap), flow(0), inv(inv) {}
  };

  F eps = (F) 1e-9;
  int s, t, n, m = 0;
  vector< vector<Edge> > g;
  vector<Edge*> prev;
  vector<C> cost;
  vi state;

  Mcmf(int n) : n(n), g(n), cost(n), state(n), prev(n), s(n - 2), t(n - 1) {}

  void add(int u, int v, C cost, F cap) {
    g[u].pb(Edge(u, v, cost, cap, sz(g[v])));
    g[v].pb(Edge(v, u, -cost, 0, sz(g[u]) - 1));
    m += 2;
  }

  bool bfs() {
    fill(all(state), 0);
    fill(all(cost), numeric_limits<C>::max());
    deque<int> qu;
    qu.push_back(s);
    state[s] = 1, cost[s] = 0;
    while (sz(qu)) {
      int u = qu.front(); qu.pop_front();
      state[u] = 2;
      for (Edge &e : g[u]) if (e.cap - e.flow > eps)
        if (cost[u] + e.cost < cost[e.v]) {
          cost[e.v] = cost[u] + e.cost;
          prev[e.v] = &e;
          if (state[e.v] == 2 || (sz(qu) && cost[qu.front()] > cost[e.v]))
            qu.push_front(e.v);
          else if (state[e.v] == 0)
            qu.push_back(e.v);
          state[e.v] = 1;
        }
    }
    return cost[t] != numeric_limits<C>::max();
  }

  pair<C, F> minCostFlow() {
    C cost = 0; F flow = 0;
    while (bfs()) {
      F pushed = numeric_limits<F>::max();
      for (Edge* e = prev[t]; e != nullptr; e = prev[e->u])
        pushed = min(pushed, e->cap - e->flow);
      for (Edge* e = prev[t]; e != nullptr; e = prev[e->u]) {
        e->flow += pushed;
        g[e->v][e->inv].flow -= pushed;
        cost += e->cost * pushed;
      }
      flow += pushed;
    }
    return make_pair(cost, flow);
  }
};