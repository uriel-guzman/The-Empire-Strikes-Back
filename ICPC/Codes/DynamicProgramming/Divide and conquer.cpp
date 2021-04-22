void solve(int cut, int l, int r, int optl, int optr) {
  if (r < l)
    return;
  int mid = (l + r) / 2;
  pair<lli, int> best = {inf, -1};
  fore (p, optl, min(mid, optr) + 1) 
    best = min(best, {dp[~cut & 1][p - 1] + cost(p, mid), p});
  dp[cut & 1][mid] = best.f;
  solve(cut, l, mid - 1, optl, best.s);
  solve(cut, mid + 1, r, best.s, optr);
} 

fore (i, 1, n + 1)
  dp[1][i] = cost(1, i);
fore (cut, 2, k + 1) 
  solve(cut, cut, n, cut, n);
