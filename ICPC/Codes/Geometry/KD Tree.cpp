struct Pt {
  // Geometry point mostly
  ld operator[](int i) const {
    return i == 0 ? x : y;
  }
};

struct KDTree {
  Pt p;
  int k;
  KDTree *left, *right;

  template <class Iter>
  KDTree(Iter l, Iter r, int k = 0) : k(k), left(0), right(0) {
    int n = r - l;
    if (n == 1) {
      p = *l;
      return;
    }
    nth_element(l, l + n / 2, r, [&](Pt a, Pt b) {
      return a[k] < b[k];
    });
    p = *(l + n / 2);
    left = new KDTree(l, l + n / 2, k ^ 1);
    right = new KDTree(l + n / 2, r, k ^ 1);
  }

  pair<ld, Pt> nearest(Pt x) {
    if (!left && !right)
      return {(p - x).norm(), p};
    vector<KDTree*> go = {left, right};
    auto delta = x[k] - p[k];
    if (delta > 0)
      swap(go[0], go[1]);
    auto best = go[0]->nearest(x);
    if (best.f > delta * delta)
      best = min(best, go[1]->nearest(x));
    return best;
  }
};