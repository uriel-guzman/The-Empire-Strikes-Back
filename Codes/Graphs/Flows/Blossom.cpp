struct Blossom {
  int n, m;
  vector<int> mate, p, d, bl;
  vector<vector<int>> b, g;

  Blossom(int n)
      : n(n),
        m(n + n / 2),
        mate(n, -1),
        b(m),
        p(m),
        d(m),
        bl(m),
        g(m, vector<int>(m, -1)) {}

  void add(int u, int v) { // 0-indexed!!!!!
    g[u][v] = u;
    g[v][u] = v;
  }

  void match(int u, int v) {
    g[u][v] = g[v][u] = -1;
    mate[u] = v;
    mate[v] = u;
  }

  vector<int> trace(int x) {
    vector<int> vx;
    while (true) {
      while (bl[x] != x) x = bl[x];
      if (!vx.empty() && vx.back() == x) break;
      vx.pb(x);
      x = p[x];
    }
    return vx;
  }

  void contract(int c, int x, int y, vector<int>& vx, vector<int>& vy) {
    b[c].clear();
    int r = vx.back();
    while (!vx.empty() && !vy.empty() && vx.back() == vy.back()) {
      r = vx.back();
      vx.pop_back();
      vy.pop_back();
    }
    b[c].pb(r);
    b[c].insert(b[c].end(), vx.rbegin(), vx.rend());
    b[c].insert(b[c].end(), vy.begin(), vy.end());
    fore (i, 0, c + 1) g[c][i] = g[i][c] = -1;
    for (int z : b[c]) {
      bl[z] = c;
      fore (i, 0, c) {
        if (g[z][i] != -1) {
          g[c][i] = z;
          g[i][c] = g[i][z];
        }
      }
    }
  }

  vector<int> lift(vector<int>& vx) {
    vector<int> A;
    while (sz(vx) >= 2) {
      int z = vx.back();
      vx.pop_back();
      if (z < n) {
        A.pb(z);
        continue;
      }
      int w = vx.back();
      int i = (sz(A) % 2 == 0 ? find(all(b[z]), g[z][w]) - b[z].begin() : 0);
      int j =
          (sz(A) % 2 == 1 ? find(all(b[z]), g[z][A.back()]) - b[z].begin() : 0);
      int k = sz(b[z]);
      int dif = (sz(A) % 2 == 0 ? i % 2 == 1 : j % 2 == 0) ? 1 : k - 1;
      while (i != j) {
        vx.pb(b[z][i]);
        i = (i + dif) % k;
      }
      vx.pb(b[z][i]);
    }
    return A;
  }

  int solve() {
    for (int ans = 0;; ans++) {
      fill(d.begin(), d.end(), 0);
      queue<int> Q;
      fore (i, 0, m) bl[i] = i;
      fore (i, 0, n) {
        if (mate[i] == -1) {
          Q.push(i);
          p[i] = i;
          d[i] = 1;
        }
      }
      int c = n;
      bool aug = false;
      while (!Q.empty() && !aug) {
        int x = Q.front();
        Q.pop();
        if (bl[x] != x) continue;
        fore (y, 0, c) {
          if (bl[y] == y && g[x][y] != -1) {
            if (d[y] == 0) {
              p[y] = x;
              d[y] = 2;
              p[mate[y]] = y;
              d[mate[y]] = 1;
              Q.push(mate[y]);
            } else if (d[y] == 1) {
              vector<int> vx = trace(x);
              vector<int> vy = trace(y);
              if (vx.back() == vy.back()) {
                contract(c, x, y, vx, vy);
                Q.push(c);
                p[c] = p[b[c][0]];
                d[c] = 1;
                c++;
              } else {
                aug = true;
                vx.insert(vx.begin(), y);
                vy.insert(vy.begin(), x);
                vector<int> A = lift(vx);
                vector<int> B = lift(vy);
                A.insert(A.end(), B.rbegin(), B.rend());
                for (int i = 0; i < sz(A); i += 2) {
                  match(A[i], A[i + 1]);
                  if (i + 2 < sz(A)) add(A[i + 1], A[i + 2]);
                }
              }
              break;
            }
          }
        }
      }
      if (!aug) return ans;
    }
  }
};