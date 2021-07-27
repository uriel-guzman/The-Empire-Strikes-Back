const int INF = 1e9;
vector<Edge> graph[N];
int dist[N];
int n, m;

void dijkstra(int s) {
  fill_n(dist, n + 1, INF);
  priority_queue< tuple<int, int> > pq; // {dist, node}
  pq.emplace(dist[s] = 0, s);
  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (dist[u] < -d)
      continue;
    for (auto &e : graph[u])
      if (dist[u] + e.dist < dist[e.v]) {
        dist[e.v] = dist[u] + e.dist;
        pq.emplace(-dist[e.v], e.v);
      }
  }
}
