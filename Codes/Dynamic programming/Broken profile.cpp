lli dp[2][N + 1][1 << N];

dp[0][0][0] = 1;
fore (c, 0, m) {
  fore (r, 0, n + 1)
    fore (mask, 0, 1 << n) {
      if (r == n) { // transition to next column
        dp[~c & 1][0][mask] += dp[c & 1][r][mask];
        continue;
      }
      if (~(mask >> r) & 1) {
        dp[c & 1][r + 1][mask | (1 << r)] += dp[c & 1][r][mask];
        if (~(mask >> (r + 1)) & 1)
          dp[c & 1][r + 2][mask] += dp[c & 1][r][mask];
      } else {
        dp[c & 1][r + 1][mask & ~(1 << r)] += dp[c & 1][r][mask];
      }
    }
  fore (r, 0, n + 1) // clear
    fore (mask, 0, 1 << n) dp[c & 1][r][mask] = 0;
}
// Answer in dp[m & 1][0][0]