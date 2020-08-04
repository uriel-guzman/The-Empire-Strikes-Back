vector<vi> scc;
int tin[N], fup[N];
bitset<N> still;
stack<int> stk;
int timer = 0;

void tarjan(int u) {
  tin[u] = fup[u] = ++timer;
  still[u] = true;
  stk.push(u);
  for (int v : graph[u]) {
    if (!tin[v])
      tarjan(v);
    if (still[v])
      fup[u] = min(fup[u], fup[v]);
  }
  if (fup[u] == tin[u]) {
    scc.pb({});
    int v;
    do {
      v = stk.top();
      stk.pop();
      still[v] = false;
      scc.back().pb(v);
    } while (v != u);
  }
}
