// How many simple paths of distance K exists.
vector<int> graph[N];
int cnt[C]; // cnt[x] store the amount of paths with length x
int sz[N];
int depth[N]; // depth[u] <- distance from root to u
int cur = -1; // <- Current subtree node
int K;
lli paths = 0;

int guni(int u, int p = 0, int len = 0) {
  sz[u] = 1;
  depth[u] = len;
  for (int &v : graph[u]) if (v != p) {
    sz[u] += guni(v, u, len + 1);
    if (sz[v] > sz[graph[u][0]] || p == graph[u][0])
      swap(v, graph[u][0]);
  }
  return sz[u];
}

void f (int u) {
  // depth[u] + need == K + 2 * depth[cur]
  // need = K + 2 * depth[cur] - depth[u]
  int need = K + 2 * depth[cur] - depth[u];
  if (need >= 0) {
    paths += cnt[need];
  }
}

void compute(int u, int p, int x, bool op) {
  if (op) {
    f(u);
  } else {
    cnt[depth[u]] += x;
  }
  for (int i = 0; i < sz(graph[u]); i++) // don't change it with a fore!!!
    if (graph[u][i] != p)
      compute(graph[u][i], u, x, op);
}

void solve(int u, int p, bool keep = 0) {
  fore (i, sz(graph[u]), 0)
    if (graph[u][i] != p) 
      solve(graph[u][i], u, !i);

  cur = u;
  for (int i = 1; i < sz(graph[u]); i++) { // <- don't change it with a fore
    int v = graph[u][i];
    if (v != p) {
      // Check paths from a node in the subtree of v to any other in the data structure. 
      compute(v, u, +1, 1); 

      // Update the data structure with subtree of v.
      compute(v, u, +1, 0); 
    }
  } 
  
  { // paths from node u to any other node.
    f(u);
    cnt[depth[u]] ++;
  } 
  
  if (!keep) 
    compute(u, p, -1, 0); // remove
}