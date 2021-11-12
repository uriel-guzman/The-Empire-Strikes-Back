struct Pt {
  ld x, y;
  ld pos(int k) const {
    return k == 0 ? x : y;
  }
};

struct KDTree {
// p.pos(0) = x, p.pos(1) = y, p.pos(2) = z
#define iter Pt* // vector<Pt>::iterator
  KDTree *left, *right;
  Pt p;
  ld val;
  int k;

  KDTree(iter b, iter e, int k = 0) : k(k), left(0), right(0) {
    int n = e - b;
    if (n == 1) {
      p = *b;
      return;
    }
    nth_element(b, b + n / 2, e, [&](Pt a, Pt b) {
      return a.pos(k) < b.pos(k);
    });
    val = (b + n / 2)->pos(k);
    left = new KDTree(b, b + n / 2, (k + 1) % 2);
    right = new KDTree(b + n / 2, e, (k + 1) % 2);
  }

  pair<ld, Pt> nearest(Pt q) {
    if (!left && !right) // take care if is needed a different one
      return make_pair((p - q).norm(), p);
    pair<ld, Pt> best;
    if (q.pos(k) <= val) {
      best = left->nearest(q);
      if (geq(q.pos(k) + sqrt(best.f), val))
        best = min(best, right->nearest(q));
    } else {
      best = right->nearest(q);
      if (leq(q.pos(k) - sqrt(best.f), val))
        best = min(best, left->nearest(q));
    }
    return best;
  }
};