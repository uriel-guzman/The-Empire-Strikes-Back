const int INF = 1e9;
vector<Edge> edges;
int dist[N];
int n, m;

void bellmandFord(int s) {
  fill_n(dist, n + 1, INF);
  dist[s] = 0;
  for (;;) {
    bool any = false;
    for (Edge& e : edges)
      if (dist[e.u] < INF)
        if (dist[e.u] + e.dist < dist[e.v]) {
          dist[e.v] = dist[e.u] + e.dist;
          any = true;
        }
    if (!any) break;
  }
}
