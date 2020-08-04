typedef struct Node* Treap;
struct Node {
  uint32_t pri = rng();
  int val;
  Treap ch[2] = {0, 0};
  int sz = 1, flip = 0;
  Node(int val) : val(val) {}
};

void push(Treap t) {
  if (!t)
    return;
  if (t->flip) {
    swap(t->ch[0], t->ch[1]);
    for (Treap ch : t->ch) if (ch) 
      ch->flip ^= 1;
    t->flip = 0;
  }
}

Treap pull(Treap t) {
  #define gsz(t) (t ? t->sz : 0)
  t->sz = 1;
  for (Treap ch : t->ch) 
    push(ch), t->sz += gsz(ch);
  return t;
}

pair<Treap, Treap> split(Treap t, int val) {
  // <= val goes to the left, > val to the right
  if (!t)
    return {t, t};
  push(t);
  if (val < t->val) {
    auto p = split(t->ch[0], val);
    t->ch[0] = p.s;
    return {p.f, pull(t)};
  }
  auto p = split(t->ch[1], val);
  t->ch[1] = p.f;
  return {pull(t), p.s};
}

pair<Treap, Treap> splitsz(Treap t, int sz) {
  // <= sz goes to the left, > sz to the right
  if (!t)
    return {t, t};
  push(t);
  if (sz <= gsz(t->ch[0])) {
    auto p = splitsz(t->ch[0], sz);
    t->ch[0] = p.s;
    return {p.f, pull(t)};
  }
  auto p = splitsz(t->ch[1], sz - gsz(t->ch[0]) - 1);
  t->ch[1] = p.f;
  return {pull(t), p.s};
}

Treap merge(Treap l, Treap r) {
  if (!l || !r)
    return l ? l : r;
  push(l), push(r);
  if (l->pri > r->pri) 
    return l->ch[1] = merge(l->ch[1], r), pull(l);
  else
    return r->ch[0] = merge(l, r->ch[0]), pull(r);
}

Treap qkth(Treap t, int k) { // 0-indexed
  if (!t)
    return t;
  push(t);
  int sz = gsz(t->ch[0]);
  if (sz == k)
    return t;
  return k < sz ? qkth(t->ch[0], k) : qkth(t->ch[1], k - sz - 1);
}

int qrank(Treap t, int val) { // 0-indexed
  if (!t)
    return -1;
  push(t);
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