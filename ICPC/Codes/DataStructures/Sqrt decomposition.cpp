int blo[N], cnt[BLOCK][K], a[N];

void update(int i, int x) {
  cnt[blo[i]][a[i]]--;
  a[i] = x;
  cnt[blo[i]][a[i]]++;
}

int query(int l, int r, int x) {  
  int tot = 0;
  while (l <= r) 
    if (l % BLOCK == 0 && l + BLOCK - 1 <= r) {
      tot += cnt[blo[l]][x];
      l += BLOCK;
    } else {
      tot += (a[l] == x);
      l++;
    }
  return tot;
}