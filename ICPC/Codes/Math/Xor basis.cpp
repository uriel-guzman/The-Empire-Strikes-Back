template <int D>
struct XorBasis {
  array<int, D> basis;
  int n = 0;
  
  XorBasis() { basis.fill(0); }

  bool insert(int x) {
    fore (i, D, 0) if ((x >> i) & 1) {
      if (!basis[i]) {
        basis[i] = x, n++;
        return 1;
      }
      x ^= basis[i];
    }
    return 0;
  }

  int get(int x) {
    int y = 0;
    fore (i, D, 0) if ((x >> i) & 1) {
      if (!basis[i]) return -1;
      x ^= basis[i];
      y |= (1 << i);
    }
    return y;
  }
};