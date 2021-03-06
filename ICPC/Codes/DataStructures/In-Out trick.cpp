vector<int> in[N], out[N];
vector<Query> queries;

fore (x, 0, N) {
  for (int i : in[x])
    add(queries[i]);
  // solve 
  for (int i : out[x])
    rem(queries[i]);
}