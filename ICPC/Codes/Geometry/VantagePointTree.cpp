struct VantagePointTree {
  struct Node {
    P p;
    ld th;
    Node *l, *r;
  } * root;

  vector<pair<ld, P>> aux;

  VantagePointTree(vector<P> &pts) {
    for (int i = 0; i < pts.size(); ++i)  
      aux.push_back({0, pts[i]});
    root = build(0, pts.size());
  }

  Node *build(int l, int r) {
    if (l == r) return 0;
    swap(aux[l], aux[l + rand() % (r - l)]);
    P p = aux[l++].second;
    if (l == r) return new Node({p});
    for (int i = l; i < r; ++i)
      aux[i].first = (p - aux[i].second).dot(p - aux[i].second);
    int m = (l + r) / 2;
    nth_element(aux.begin() + l, aux.begin() + m, aux.begin() + r);
    return new Node({p, sqrt(aux[m].first), build(l, m), build(m, r)});
  }

  priority_queue<pair<ld, Node *>> que;

  void k_nn(Node *t, P p, int k) {
    if (!t) return;
    ld d = (p - t->p).length();
    if (que.size() < k)
      que.push({d, t});
    else if (ge(que.top().first, d)) {
      que.pop();
      que.push({d, t});
    }
    if (!t->l && !t->r) return;
    if (le(d, t->th)) {
      k_nn(t->l, p, k);
      if (leq(t->th - d, que.top().first)) k_nn(t->r, p, k);
    } else {
      k_nn(t->r, p, k);
      if (leq(d - t->th, que.top().first)) k_nn(t->l, p, k);
    }
  }

  vector<P> k_nn(P p, int k) {
    k_nn(root, p, k);
    vector<P> ans;
    for (; !que.empty(); que.pop())  
      ans.push_back(que.top().second->p);
    reverse(ans.begin(), ans.end());
    return ans;
  }
};