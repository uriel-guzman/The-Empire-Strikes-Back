template <class Node>
struct Lazy {
  int l, r;
  Lazy *left, *right;
  Node node;

  template <class Arr>
  Lazy(int l, int r, Arr& a) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      node.val = {a[l]};
      return;
    }
    int m = (l + r) >> 1;
    left = new Lazy(l, m, a);
    right = new Lazy(m + 1, r, a);
    pull();
  }

  void push() {
    if (node.lazy()) {
      int m = (l + r) >> 1;
      left->node.apply(l, m, node.lazy);
      right->node.apply(m + 1, r, node.lazy);
      node.lazy = {};
    }
  }

  void pull() {
    node.val = left->node.val + right->node.val;
  }

  template <class... Args>
  void update(int ll, int rr, const Args&... args) {
    if (rr < l || r < ll)
      return;
    if (ll <= l && r <= rr) {
      node.apply(l, r, typename Node::Lazy(args...));
      return;
    }
    push();
    left->update(ll, rr, args...);
    right->update(ll, rr, args...);
    pull();
  }

  auto query(int ll, int rr) {
    if (rr < l || r < ll)
      return typename Node::Value();
    if (ll <= l && r <= rr)
      return node.val;
    push();
    return left->query(ll, rr) + right->query(ll, rr);
  }
};

struct Node {
  struct Lazy {
    int add;
    Lazy(int x = 0) : add(x) {}

    inline bool operator()() const {
      return add != 0;
    }
  } lazy;

  struct Value {
    int sum;
    Value(int x = 0) : sum(x) {}

    friend Value operator+(Value l, const Value& r) {
      l.sum += r.sum;
      return l;
    }
  } val;

  inline void apply(int l, int r, const Lazy& tag) {
    val.sum += tag.add;
    lazy.add += tag.add;
  }
};