fore (i, 0, n)
  for (int x = MaxW; x >= w[i]; x--) umax(dp[x], dp[x - w[i]] + cost[i]);