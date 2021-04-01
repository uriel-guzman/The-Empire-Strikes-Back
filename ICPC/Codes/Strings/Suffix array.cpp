template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, ra, lcp;
  
  SuffixArray(const T &a) : n(sz(a) + 1), s(a), sa(n), ra(n), lcp(n) {
    s.pb(0); // something 
    for (int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++) {
      vector<int> nsa(sa), nra(n), cnt(max(n, 260));
      fore (i, 0, n) nsa[i] = (nsa[i] - k + n) % n, cnt[ra[i]]++;
      partial_sum(all(cnt), cnt.begin());
      fore (i, n, 0) sa[--cnt[ra[nsa[i]]]] = nsa[i];
      int r = 0;
      fore (i, 1, n) {
        if (ra[sa[i]] != ra[sa[i - 1]] || ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
        nra[sa[i]] = r; 
      }
      ra = nra;
      if (ra[sa[n - 1]] == n - 1) break;
    }
    for (int i = 0, k = 0; i < n; i++, k -= !!k) {
      if (ra[i] == n - 1) {
        k = 0;
        continue;
      }
      int j = sa[ra[i] + 1];
      while (i + k < n and j + k < n and s[i + k] == s[j + k]) k++;
      lcp[ra[i]] = k;
    }
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
