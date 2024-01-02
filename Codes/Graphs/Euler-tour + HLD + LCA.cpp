int par[N], nxt[N], depth[N], sz[N];
int tin[N], tout[N], who[N], timer = 0;

int dfs(int u) {
  sz[u] = 1;
  for (auto& v : graph[u])
    if (v != par[u]) {
      par[v] = u;
      depth[v] = depth[u] + 1;
      sz[u] += dfs(v);
      if (graph[u][0] == par[u] || sz[v] > sz[graph[u][0]])
        swap(v, graph[u][0]);
    }
  return sz[u];
}

void hld(int u) {
  tin[u] = ++timer, who[timer] = u;
  for (auto& v : graph[u])
    if (v != par[u]) {
      nxt[v] = (v == graph[u][0] ? nxt[u] : v);
      hld(v);
    }
  tout[u] = timer;
}

template <bool OverEdges = 0, class F>
void processPath(int u, int v, F f) {
  for (; nxt[u] != nxt[v]; u = par[nxt[u]]) {
    if (depth[nxt[u]] < depth[nxt[v]])
      swap(u, v);
    f(tin[nxt[u]], tin[u]);
  }
  if (depth[u] < depth[v])
    swap(u, v);
  f(tin[v] + OverEdges, tin[u]);
}

int lca(int u, int v) {
  int last = -1;
  processPath(u, v, [&](int l, int r) {
    last = who[l];
  });
  return last;
}

void updatePath(int u, int v, lli z) {
  processPath(u, v, [&](int l, int r) {
    tree->update(l, r, z);
  });
}

void updateSubtree(int u, lli z) {
  tree->update(tin[u], tout[u], z);
}

lli queryPath(int u, int v) {
  lli sum = 0;
  processPath(u, v, [&](int l, int r) {
    sum += tree->query(l, r);
  });
  return sum;
}

lli queryPathWithOrder(int u, int v, int x) {
  int _lca = lca(u, v); assert(_lca != -1);

  vector<pair<int, int>> firstHalf, secondHalf, ranges;
  processPath(u, _lca, [&] (int l, int r) {
    firstHalf.push_back(make_pair(r, l));
  });

  processPath(_lca, v, [&] (int l, int r) {
    l += tin[_lca] == l;
    if (l <= r) {
      secondHalf.push_back(make_pair(l, r));
    }
  });
  reverse(all(secondHalf));

  ranges = firstHalf;
  ranges.insert(end(ranges), begin(secondHalf), end(secondHalf));

  int who = -1;
  for (auto [begin, end] : ranges) {
    // if begin <= end: left to right, aka. normal
    // if begin > end: right to left, 
    // e.g. begin = 3, end = 1
    // order must go 3, 2, 1

    // e.g. first node in the path(u, v) with value less than or equal to x
    if ((who = tree->solve(begin, end, x)) != -1) {
      break;
    }
  }

  return who;
}

lli querySubtree(int u) {
  return tree->query(tin[u], tout[u]);
}

