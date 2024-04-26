int tin[N], fup[N];
bitset<N> still;
stack<int> stk;
int timer = 0;

void tarjan(int u) {
  tin[u] = fup[u] = ++timer;
  still[u] = true;
  stk.push(u);
  for (auto& v : graph[u]) {
    if (!tin[v]) tarjan(v);
    if (still[v]) fup[u] = min(fup[u], fup[v]);
  }
  if (fup[u] == tin[u]) {
    int v;
    do {
      v = stk.top();
      stk.pop();
      still[v] = false;
      // u and v are in the same scc
    } while (v != u);
  }
}
