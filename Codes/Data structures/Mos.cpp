struct Query {
  int l, r, i;
};

vector<Query> queries;

const int BLOCK = sqrt(N);
sort(all(queries), [&](Query& a, Query& b) {
  const int ga = a.l / BLOCK, gb = b.l / BLOCK;
  if (ga == gb)
    return a.r < b.r;
  return ga < gb;
});

int l = queries[0].l, r = l - 1;
for (auto& q : queries) {
  while (r < q.r) add(++r);
  while (r > q.r) rem(r--);
  while (l < q.l) rem(l++);
  while (l > q.l) add(--l);
  ans[q.i] = solve();
}