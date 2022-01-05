lli dp[N][N];
int opt[N][N];

fore (len, 1, n + 1)
  fore (l, 0, n) {
    int r = l + len - 1;
    if (r > n - 1)
      break;
    if (len <= 2) {
      dp[l][r] = 0;
      opt[l][r] = l;
      continue;
    }
    dp[l][r] = INF;
    fore (k, opt[l][r - 1], opt[l + 1][r] + 1) {
      lli cur = dp[l][k] + dp[k][r] + cost(l, r);
      if (cur < dp[l][r]) {
        dp[l][r] = cur;
        opt[l][r] = k;
      }
    }
  }
