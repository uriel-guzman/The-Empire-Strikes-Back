typedef struct Node* Treap;
struct Node {
  Treap ch[2] = {0, 0}, p = 0;
  uint32_t pri = rng();
  int sz = 1, rev = 0;
  int val, sum = 0;

  void push() {
    if (rev) {
      swap(ch[0], ch[1]);
      for (auto ch : ch) if (ch != 0) {
        ch->rev ^= 1;
      } 
      rev = 0;
    }
  }
 
  Treap pull() {
    #define gsz(t) (t ? t->sz : 0)
    #define gsum(t) (t ? t->sum : 0)
    sz = 1, sum = val;
    for (auto ch : ch) if (ch != 0) {
      ch->push();
      sz += ch->sz;
      sum += ch->sum;
      ch->p = this;
    }
    p = 0;
    return this;
  }

  Node(int val) : val(val) {}
};

pair<Treap, Treap> split(Treap t, int val) {
  // <= val goes to the left, > val to the right
  if (!t) 
    return {t, t};
  t->push();
  if (val < t->val) {
    auto p = split(t->ch[0], val);
    t->ch[0] = p.s;
    return {p.f, t->pull()};
  } else {
    auto p = split(t->ch[1], val);
    t->ch[1] = p.f;
    return {t->pull(), p.s};
  }
}

Treap merge(Treap l, Treap r) {
  if (!l || !r)
    return l ? l : r;
  l->push(), r->push();
  if (l->pri > r->pri) 
    return l->ch[1] = merge(l->ch[1], r), l->pull();
  else
    return r->ch[0] = merge(l, r->ch[0]), r->pull();
}

Treap qkth(Treap t, int k) { // 0-indexed
  if (!t)
    return t;
  t->push();
  int sz = gsz(t->ch[0]);
  if (sz == k)
    return t;
  return k < sz ? qkth(t->ch[0], k) : qkth(t->ch[1], k - sz - 1);
}

int qrank(Treap t, int val) { // 0-indexed
  if (!t)
    return -1;
  t->push();
  if (val < t->val)
    return qrank(t->ch[0], val);
  if (t->val == val)
    return gsz(t->ch[0]);
  return gsz(t->ch[0]) + qrank(t->ch[1], val) + 1;
}

Treap insert(Treap t, int val) {
  auto p1 = split(t, val);
  auto p2 = split(p1.f, val - 1);
  return merge(p2.f, merge(new Node(val), p1.s));
}

Treap erase(Treap t, int val) {
  auto p1 = split(t, val);
  auto p2 = split(p1.f, val - 1);
  return merge(p2.f, p1.s);
}

// Use this split for implicit treap aka rope
pair<Treap, Treap> splitsz(Treap t, int sz) {
  // <= sz goes to the left, > sz to the right
  if (!t) 
    return {t, t};
  t->push();
  if (sz <= gsz(t->ch[0])) {
    auto p = splitsz(t->ch[0], sz);
    t->ch[0] = p.s;
    return {p.f, t->pull()};
  } else {
    auto p = splitsz(t->ch[1], sz - gsz(t->ch[0]) - 1);
    t->ch[1] = p.f;
    return {t->pull(), p.s};
  }
}