vector<edge> graph[N];
int dist[N];
int n, m;

void bfs(int s) {
  fill_n(dist, n + 1, -1);
  queue<int> qu;
  dist[s] = 0;
  qu.push(s);
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    for (edge &e : graph[u])
      if (dist[e.v] == -1) {
        dist[e.v] = dist[u] + e.dist;
        qu.push(e.v);
      }
  }
}
