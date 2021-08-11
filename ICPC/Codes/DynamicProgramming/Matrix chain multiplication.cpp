int dp(int l, int r) {
  if (l > r)
    return 0;
  int &ans = mem[l][r];
  if (!done[l][r]) {
    done[l][r] = true, ans = inf;
    fore (k, l, r + 1) // split in [l, k] [k + 1, r]
      ans = min(ans, dp(l, k) + dp(k + 1, r) + add);
  }
  return ans;
}
