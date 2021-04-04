template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, rk, lcp;
  
  SuffixArray(const T &a) : n(sz(a) + 1), s(a), sa(n), rk(n), lcp(n) {
    s.pb(0);
    fore (i, 0, n) sa[i] = i, rk[i] = s[i];
    for (int k = 0; k < n; k ? k *= 2 : k++) {
      vector<int> nsa(sa), nrk(n), cnt(max(260, n));
      fore (i, 0, n) nsa[i] = (nsa[i] - k + n) % n, cnt[rk[i]]++;
      partial_sum(all(cnt), cnt.begin());
      fore (i, n, 0) sa[--cnt[rk[nsa[i]]]] = nsa[i];
      for (int i = 1, r = 0; i < n; i++) 
        nrk[sa[i]] = r += rk[sa[i]] != rk[sa[i - 1]] || rk[(sa[i] + k) % n] != rk[(sa[i - 1] + k) % n];;
      rk.swap(nrk);
      if (rk[sa[n - 1]] == n - 1) break;
    }
    for (int i = 0, j = rk[lcp[0] = 0], k = 0; i < n - 1; i++, k++) 
      while (k >= 0 && s[i] != s[sa[j - 1] + k])
        lcp[j] = k--, j = rk[sa[j] + 1];  
  }

  auto at(int i, int j) {
    return sa[i] + j < n ? s[sa[i] + j] : 'z' + 1;
  }

  int count(T &t) {
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