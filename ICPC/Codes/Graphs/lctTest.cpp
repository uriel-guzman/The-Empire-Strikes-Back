#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 
#endif

#define df(b, e) ((b) > (e))
#define fore(i, b, e) for (auto i = (b) - df(b, e); i != e - df(b, e); i += 1 - 2 * df(b, e))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

typedef long long lli;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1000;

typedef struct Node* Splay;
struct Node {
  int val, mx = 0;
  Splay ch[2], p;
  int sz = 1, flip = 0;

  Node(int val) : val(val) {
    mx = val;
  }
};

void push(Splay u) {
  if (!u || !u->flip)
    return;
  swap(u->ch[0], u->ch[1]);
  for (Splay v : u->ch)
    if (v) v->flip ^= 1;
  u->flip ^= 1;
}

void pull(Splay u) {
  u->sz = 1, u->mx = u->val;
  for (Splay v : u->ch) if (v) {
    push(v);
    u->sz += v->sz;
    u->mx = max(u->mx, v->mx);
  }
}

int dir(Splay u) {
  if (!u->p) return -2; // root of the LCT component
  if (u->p->ch[0] == u) return 0; // left child
  if (u->p->ch[1] == u) return 1; // right child
  return -1; // root of current splay tree
}

void add(Splay u, Splay v, int d) {
  if (v) v->p = u;
  if (d >= 0) u->ch[d] = v;
}

void rot(Splay u) { // assume p and p->p propagated
  int x = dir(u);
  Splay g = u->p; 
  add(g->p, u, dir(g));
  add(g, u->ch[x ^ 1], x);
  add(u, g, x ^ 1);
  pull(g), pull(u);
}

void splay(Splay u) {
  #define isRoot(u) (dir(u) < 0)
  while (!isRoot(u) && !isRoot(u->p)) {
    push(u->p->p), push(u->p), push(u);
    rot(dir(u) == dir(u->p) ? u->p : u);
    rot(u);
  }
  if (!isRoot(u)) push(u->p), push(u), rot(u);
  push(u);
}

// puts u on the preferred path, splay (right subtree is empty)
void access(Splay u) {
  for (Splay v = u, last = 0; v; v = v->p) {
    splay(v); // now switch virtual children, i don't know what this means
    // if (last) v->vsub -= last->sub;
    // if (v->ch[1]) v->vsub += v->ch[1]->sub;
    v->ch[1] = last, pull(v), last = v;
  }
  splay(u);
}

Splay lca(Splay u, Splay v) {
  if (u == v) return u;
  access(u), access(v);
  if (!u->p) return NULL;
  splay(u);
  return u->p ?: u;
}

bool connected(Splay u, Splay v) {
  return lca(u, v);  
}

void rootify(Splay u) {
  access(u), u->flip ^= 1, access(u);
  // assert(!u->ch[0] && !u->ch[1]);
}

void link(Splay u, Splay v) { // make u parent of v
  if (!connected(u, v)) {
    rootify(v), access(u);
    add(v, u, 0), pull(v);
  }
}

void cut(Splay u) { // cut u from its parent
  access(u);
  u->ch[0] = u->ch[0]->p = 0;
  pull(u);
}

void cut(Splay u, Splay v) { // if u, v adj in tree
  rootify(u), access(v), cut(v);
}

Splay getRoot(Splay u) {
  access(u);
  while (u->ch[0])
    u = u->ch[0], push(u);
  return access(u), u;
}

Splay query(Splay u, Splay v) { 
  return rootify(u), access(v), v;
}

Splay lct[N];

ostream & operator << (ostream &os, Splay s) {
  if (s == NULL)
    return os << "NULL";
  else
    return os << s->val;
}



int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);
  int n = N;
  fore (i, 0, n)
    lct[i] = new Node(i);
  vector<ii> edges;

  auto conn = [&](int a, int b) {
    vector<int> dp(n + 1, -1);
    dp[a] = lct[a]->val;
    for (int ch = 1; ch >= 0; ch--) {
      for (auto p : edges) {
        for (int it = 0; it < 2; ++it) {
          if (dp[p.first] != -1 && dp[p.second] == -1) {
            dp[p.second] = max(dp[p.first], lct[p.second]->val);
            ch = 1;
          }
          swap(p.first, p.second);
        }
      }
    }
    return dp[b];
  };
  
  uniform_int_distribution<int> uid(0, 4);
  uniform_int_distribution<int> getNode(0, n - 1);

  int clink = 0, ccut = 0, cquery = 0, cupdate = 0, csame = 0;

  for (int i = 0; i < 10000; ++i) {
    int t = uid(rng);
    debug(i, t);

 
    if (t == 0) {
      clink++;
      int a = getNode(rng);
      int b = getNode(rng);
      while (b == a)
        b = getNode(rng);
      debug("connect them", a, b);
      if (conn(a, b) == -1) {
        link(lct[a], lct[b]);
        edges.emplace_back(a, b);
      }
    }  

  
    if (t == 1) {
      if (edges.empty()) {
        i--;
        continue;
      }
      ccut++;
      int pos = rng() % edges.size();
      swap(edges[pos], edges.back());
      debug("cut", edges.back(), sz(edges));
      int a = edges.back().f;
      int b = edges.back().s;
      cut(lct[a], lct[b]);
      edges.pop_back();
    } 
    
    
    if (t == 2) {
      cupdate++;
      int node = getNode(rng);
      access(lct[node]);
      lct[node]->val = rng() % 100 + 1;
      pull(lct[node]);
      debug("update", node, lct[node]->val);
    }
    
    if (t == 3) {
      if (edges.empty()) {
        i--;
        continue;
      }
      cquery++;
      int pos = rng() % edges.size();
      int a = edges[pos].f;
      int b = edges[pos].s;
      debug("query", a, b);
      int expected = conn(a, b);
      if (expected != -1) {
        Splay c = query(lct[a], lct[b]);
        int actual = c->mx;
        debug(c, expected, actual);
        assert(expected == actual);
      } else {
        debug("no connected");
      }
    } 
    
    if (t == 4) {
      csame++;
      int a = getNode(rng);
      int b = getNode(rng);
      while (b == a)
        b = getNode(rng);
      debug("connected", a, b);
      int expected = (conn(a, b) != -1);
      int actual = connected(lct[a], lct[b]);
      debug(expected, actual);
      assert(expected == actual);
    }
    
    debug("");
  }

  debug("everything ok");
  debug(clink, ccut, cupdate, cquery, csame);

  

  /*
  while (1) {
    // debug("next operation");
    string op;
    cin >> op;
    // debug(op);
    if (op == "link") {
      int u, v;
      cin >> u >> v;
      lct.link(u, v);
    } 
    if (op == "cut") {
      int u, v;
      cin >> u >> v;
      lct.cut(u, v);
    }
    if (op == "update") {
      int u, x;
      cin >> u >> x;
      lct.tree[u].v = x;
      lct.tree[u].pull();
    }
    if (op == "query") {
      int u, v;
      cin >> u >> v;
      int lca = lct.getPath(u, v);
      // debug(lca, lct.tree[lca].dp);
    }
    if (op == "same") {
      int u, v;
      cin >> u >> v;
      // debug(lct.connected(u, v));
    }
    // debug(lct.tree);
    // debug("");
  }*/

  return 0;
}