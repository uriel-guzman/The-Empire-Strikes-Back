vi graph[N];
lli dp[N], h[N];

lli f(lli x) {
  // K * n <= 9e18
  static uniform_int_distribution<lli> uid(1, K);
  if (!mp.count(x))
    mp[x] = uid(rng);
  return mp[x];
}

lli hsh(int u, int p = -1) { 
  dp[u] = h[u] = 0;
  for (int v : graph[u]) {
    if (v == p)
      continue;
    dp[u] += hsh(v, u);
  }
  return h[u] = f(dp[u]);
}