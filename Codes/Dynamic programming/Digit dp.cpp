#define state [i][x][small][big][nonzero]
int dp(int i, int x, bool small, bool big, bool nonzero) {
  if (i == sz(r)) return x % k == 0 && nonzero;
  int& ans = mem state;
  if (done state != timer) {
    done state = timer;
    ans = 0;
    int lo = small ? 0 : l[i] - '0';
    int hi = big ? 9 : r[i] - '0';
    fore (y, lo, max(lo, hi) + 1) {
      bool small2 = small | (y > lo);
      bool big2 = big | (y < hi);
      bool nonzero2 = nonzero | (y > 0);
      ans += dp(i + 1, (x * 10 + y) % k, small2, big2, nonzero2);
    }
  }
  return ans;
}
