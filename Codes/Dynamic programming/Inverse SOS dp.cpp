// dp[mask] = Sum of all dp[x] such that 'mask' is a submask of 'x'
fore (i, 0, N)
  for (int mask = (1 << N) - 1; mask >= 0; mask--)
    if (mask >> i & 1) dp[mask ^ (1 << i)] += dp[mask];