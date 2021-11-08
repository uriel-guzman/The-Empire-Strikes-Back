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

  optional<int> find(int x) {
    // which number is needed to generate x
    // num ^ (num ^ x) = x
    int num = 0; 
    fore (i, D, 0) if ((x >> i) & 1) {
      if (!basis[i]) return nullopt;
      x ^= basis[i];
      num |= (1 << i);
    }
    return optional(num);
  }

  optional<int> operator [](lli k) {
    lli tot = (1LL << n);
    if (k > tot) return nullopt;
    int num = 0;
    fore (i, D, 0) if (basis[i]) {
      lli low = tot / 2;
      if ((low < k && ((num >> i) & 1) == 0) || (low >= k && ((num >> i) & 1))) 
        num ^= basis[i];
      if (low < k) k -= low;
      tot /= 2;
    }
    return optional(num);
  }
};
