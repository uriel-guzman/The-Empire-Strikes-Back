vector<int> order;
int indeg[N];

void topologicalSort() { // first fill the indeg[]
  queue<int> qu;
  fore (u, 1, n + 1)
    if (indeg[u] == 0)
      qu.push(u);
  while (!qu.empty()) {
    int u = qu.front();
    qu.pop();
    order.pb(u);
    for (auto& v : graph[u])
      if (--indeg[v] == 0)
        qu.push(v);
  }
}