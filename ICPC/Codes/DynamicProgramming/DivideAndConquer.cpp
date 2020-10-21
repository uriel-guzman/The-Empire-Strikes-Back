void dc(int cut, int l, int r, int optl, int optr) {
  if (r < l)
    return;
  int mid = (l + r) / 2;
  pair<lli, int> best = {inf, -1};
  fore (p, optl, min(mid, optr) + 1) {
    lli nxt = dp[~cut & 1][p - 1] + cost(p, mid);
    if (nxt < best.f)
      best = {nxt, p};
  }
  dp[cut & 1][mid] = best.f;
  int opt = best.s;
  dc(cut, l, mid - 1, optl, opt);
  dc(cut, mid + 1, r, opt, optr);
} 

fore (i, 1, n + 1)
  dp[1][i] = cost(1, i);
fore (cut, 2, k + 1) 
  dc(cut, cut, n, cut, n);