vector<Query> queries;
// N = 1e6, so aprox. sqrt(N) +/- C
uniform_int_distribution<int> dis(970, 1030); 
const int blo = dis(rng);
sort(all(queries), [&](Query a, Query b) {
  const int ga = a.l / blo, gb = b.l / blo;
  if (ga == gb) 
    return (ga & 1) ? a.r < b.r : a.r > b.r;
  return a.l < b.l;
});
int l = queries[0].l, r = l - 1;
for (Query &q : queries) {
  while (r < q.r)
    add(++r);
  while (r > q.r)
    rem(r--);
  while (l < q.l)
    rem(l++);
  while (l > q.l)
    add(--l);
  ans[q.i] = solve();
}