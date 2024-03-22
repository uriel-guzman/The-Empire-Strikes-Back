int cdp[N], sz[N];
bitset<N> rem;

int dfsz(int u, int p = -1) {
  sz[u] = 1;
  for (int v : graph[u])
    if (v != p && !rem[v]) sz[u] += dfsz(v, u);
  return sz[u];
}

int centroid(int u, int size, int p = -1) {
  for (int v : graph[u])
    if (v != p && !rem[v] && 2 * sz[v] > size) return centroid(v, size, u);
  return u;
}

void solve(int u, int p = -1) {
  cdp[u = centroid(u, dfsz(u))] = p;
  rem[u] = true;
  for (int v : graph[u])
    if (!rem[v]) solve(v, u);
}