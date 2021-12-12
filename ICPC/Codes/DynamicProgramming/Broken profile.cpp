lli dp[2][1 << N][N]
dp[0][0][0] = 1;

fore (c, 0, m) {
  fore (r, 0, n + 1) {
    fore (mask, 0, 1 << n) {
      if (r == n) {
        dp[~c & 1][mask][0] += dp[c & 1][mask][r];
        continue;
      }

      if (~(mask >> r) & 1) {
        dp[c & 1][mask | (1 << r)][r + 1] += dp[c & 1][mask][r];

        if (~(mask >> (r + 1)) & 1)
          dp[c & 1][mask][r + 2] += dp[c & 1][mask][r];
      } else {
        dp[c & 1][mask & ~(1 << r)][r + 1] += dp[c & 1][mask][r];
      }
    }
  }

  fore (r, 0, n + 1) 
    fore (mask, 0, 1 << n)
      dp[c & 1][mask][r] = 0;
}

// Answer in dp[m][0][0]
