const int BLOCK = sqrt(N);

void update(int i) {}

int query(int l, int r) {
  while (l <= r)
    if (l % BLOCK == 0 && l + BLOCK - 1 <= r) {
      // solve for block
      l += BLOCK;
    } else {
      // solve for individual element
      l++;
    }
}
