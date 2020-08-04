vi order;
int indeg[N];

void topsort() { // first fill the indeg[]
  queue<int> qu;
  fore (u, 1, n + 1)
    if (indeg[u] == 0)
      qu.push(u);
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    order.pb(u);
    for (int v : graph[u])
      if (--indeg[v] == 0)
        qu.push(v);
  }
}


vi order;
int indeg[N];

void topsort() { // first fill the indeg[]
  fore (u, 1, n + 1)
    if (indeg[u] == 0)
      order.pb(u);
  fore (i, 0, sz(order)) {
    int u = order[i];
    for (int v : graph[u])
      if (--indeg[v] == 0) 
        order.pb(v);
  }
}