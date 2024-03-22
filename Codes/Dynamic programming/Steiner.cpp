// Connect special nodes by a minimum spanning tree
// special nodes [0, k)
fore (u, k, n)
  fore (a, 0, k) umin(dp[u][1 << a], dist[u][a]);
fore (A, 0, (1 << k))
  fore (u, k, n) {
    for (int B = A; B > 0; B = (B - 1) & A)
      umin(dp[u][A], dp[u][B] + dp[u][A ^ B]);
    fore (v, k, n) umin(dp[v][A], dp[u][A] + dist[u][v]);
  }
