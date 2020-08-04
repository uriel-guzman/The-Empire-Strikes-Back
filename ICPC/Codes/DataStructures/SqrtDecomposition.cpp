int blo[N], cnt[N][B], a[N];

void update(int i, int x) {
  cnt[blo[i]][x]--;
  a[i] = x;
  cnt[blo[i]][x]++;
}

int query(int l, int r, int x) {  
  int tot = 0;
  while (l <= r) 
    if (l % B == 0 && l + B - 1 <= r) {
      tot += cnt[blo[l]][x];
      l += B;
    } else {
      tot += (a[l] == x);
      l++;
    }
  return tot;
}