// N = amount of bits
// dp[mask] = Sum of all dp[x] such that 'x' is a submask of 'mask'
fore (i, 0, N) {
  fore (mask, 0, 1 << N) {
    if (mask >> i & 1) {
      dp[mask] += dp[mask ^ (1 << i)];
    }
  }
}