int lg[N + 1], sp[1 + __lg(N)][N]; 

int query(int l, int r) {
  int sum = 0LL;
  fore (k, 1 + lg[N], 0)
    if (l + (1 << k) - 1 <= r) {
      sum += sp[k][l];
      l += (1 << k);
    }
  return sum;
}

int query(int l, int r) {
  int k = lg[r - l + 1]; 
  return min(sp[k][l], sp[k][r - (1 << k) + 1]);
}

void sparse() {
  fore (i, 2, N + 1)
    lg[i] = lg[i >> 1] + 1;
  fore (i, 0, n)
    sp[0][i] = a[i];
  for (int k = 1; (1 << k) <= n; k++)
    fore (l, 0, n - (1 << k) + 1) {
      int r = l + (1 << (k - 1));
      sp[k][l] = min(sp[k - 1][l], sp[k - 1][r]);
    }
}
