struct Seg {
  int l, r;
  Seg *left, *right;
  int sum;

  template <class Arr>
  Seg(int l, int r, Arr& a, vector<Seg>& mem) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    mem.emplace_back(Seg(l, m, a, mem));
    left = &mem.back();
    mem.emplace_back(Seg(m + 1, r, a, mem));
    right = &mem.back();
    sum = left->sum + right->sum;
  }

  // ...
};

vector<int> a = {1, 2, 3, 4, 5};
vector<Seg> mem;
mem.reserve(2 * n - 1);
Seg tree(0, a.size() - 1, a, mem);
