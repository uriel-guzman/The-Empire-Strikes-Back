struct Edge {
  int v, w;
};

struct Data {
  int u;
  lli d;

  bool operator()(const Data& other) const {
    return !(d < other.d);
  }
};

vector<Edge> graph[N];
int dist[N];

void dijkstra(int s) {
  fill_n(dist, n + 1, INF);
  priority_queue<Data> pq; // {dist, node}
  pq.push({s, dist[s] = 0});

  while (!pq.empty()) {
    auto [u, d] = pq.top();
    pq.pop();

    if (dist[u] < d)
      continue;

    for (auto [v, w] : graph[u])
      if (umin(dist[v], dist[u] + w))
        pq.push({v, dist[v]});
  }
}
