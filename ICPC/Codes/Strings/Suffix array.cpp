struct SuffixArray {
  int n;
  string s;
  vector<int> sa, lcp;
  
  SuffixArray(string &s) : n(sz(s) + 1), s(s), sa(n), lcp(n) {
    vector<int> top(max(256, n)), rk(n);
    fore (i, 0, n) top[rk[i] = s[i] & 255]++;
    partial_sum(all(top), top.begin());
    fore (i, 0, n) sa[--top[rk[i]]] = i;
    vector<int> sb(n);
    for (int len = 1, j; len < n; len <<= 1) {
      fore (i, 0, n) {
        j = (sa[i] - len + n) % n;
        sb[top[rk[j]]++] = j;
      }
      sa[sb[top[0] = 0]] = j = 0;
      fore (i, 1, n) {
        if (rk[sb[i]] != rk[sb[i - 1]] || rk[sb[i] + len] != rk[sb[i - 1] + len])
          top[++j] = i;
        sa[sb[i]] = j;
      }
      copy(all(sa), rk.begin());
      copy(all(sb), sa.begin());
      if (j >= n - 1)
        break;
    }
    for (int i = 0, j = rk[lcp[0] = 0], k = 0; i < n - 1; i++, k++) 
      while (k >= 0 && s[i] != s[sa[j - 1] + k])
        lcp[j] = k--, j = rk[sa[j] + 1];  
  }

  char at(int i, int j) {
    int k = sa[i] + j;
    return k < n ? s[k] : 'z' + 1;
  }

  int count(string &t) {
    ii lo(0, n - 1), hi(0, n - 1);
    fore (i, 0, sz(t)) {
      while (lo.f + 1 < lo.s) {
        int mid = (lo.f + lo.s) / 2;
        (at(mid, i) < t[i] ? lo.f : lo.s) = mid;
      }
      while (hi.f + 1 < hi.s) {
        int mid = (hi.f + hi.s) / 2;
        (t[i] < at(mid, i) ? hi.s : hi.f) = mid;
      }
      int p1 = (at(lo.f, i) == t[i] ? lo.f : lo.s);
      int p2 = (at(hi.s, i) == t[i] ? hi.s : hi.f);
      if (at(p1, i) != t[i] || at(p2, i) != t[i] || p1 > p2) 
        return 0;
      lo = hi = ii(p1, p2);
    }
    return lo.s - lo.f + 1;
  }
};
