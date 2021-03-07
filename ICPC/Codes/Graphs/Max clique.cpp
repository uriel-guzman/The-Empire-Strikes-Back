template <class F>
void cliques(vector<bs> &graph, F fun, bs p = ~B(), bs x = {}, bs r = {}) {
  if (!p.any()) {
    if (!x.any())
      fun(r);
    return;
  }
  auto q = (p | x)._Find_first();
  auto cands = p & ~graph[q];
  fore (i, 0, sz(graph)) if (cands[i]) {
    r[i] = 1;
    cliques(graph, fun, p & graph[i], x & graph[i], r);
    r[i] = p[i] = 0; x[i] = 1;
  }
}