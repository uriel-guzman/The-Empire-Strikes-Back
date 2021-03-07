vector<Query> queries;

// N = 1e6, so aprox. sqrt(N) +/- C
const int blo = sqrt(N);
sort(all(queries), [&] (Query &a, Query &b) {
  const int ga = a.l / blo, gb = b.l / blo;
  if (ga == gb) 
    return a.r < b.r; 
  return a.l < b.l;
});

int l = queries[0].l, r = l - 1;
for (Query &q : queries) {
  while (r < q.r) add(++r);
  while (r > q.r) rem(r--);
  while (l < q.l) rem(l++);
  while (l > q.l) add(--l);
  ans[q.i] = solve();
}