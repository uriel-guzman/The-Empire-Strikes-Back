// dp[mask] = Sum of all dp[x] where x is a submask of mask
fore (i, 0, N) // N = amount of bits
  fore (mask, 0, 1 << N)
    if (mask >> i & 1) dp[mask] += dp[mask ^ (1 << i)];
// dp[mask] = Sum of all dp[x] where mask is a submask of x
fore (i, 0, N)
  for (int mask = (1 << N) - 1; mask >= 0; mask--)
    if (mask >> i & 1) dp[mask ^ (1 << i)] += dp[mask];