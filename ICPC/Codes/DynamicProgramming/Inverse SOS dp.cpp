// N = amount of bits
// dp[mask] = Sum of all dp[x] such that 'mask' is a submask of 'x'
fore (i, 0, N) {
  fore (mask, 1 << N, 0) 
    if (mask >> i & 1) {
      dp[mask ^ (1 << i)] += dp[mask];
    }