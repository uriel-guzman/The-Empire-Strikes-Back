int g[N][N];
int dist[N][N];
int n;

void floydWarshall() {
  fore (u, 1, n + 1)
    fore (v, 1, n + 1) dist[u][v] = (u == v ? 0 : g[u][v]);
  fore (k, 1, n + 1)
    fore (u, 1, n + 1)
      fore (v, 1, n + 1) umin(dist[u][v], dist[u][k] + dist[k][v]);
}
