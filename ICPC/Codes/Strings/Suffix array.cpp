template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, rk, lcp;
  
  SuffixArray(const T &a) : n(sz(a) + 1), s(a), sa(n), rk(n), lcp(n) {
    s.pb(0);
    fore (i, 0, n) sa[i] = i, rk[i] = s[i];
    vector<int> nsa(n), nrk(n), cnt(max(260, n));
    for (int k = 0; k < n; k ? k *= 2 : k++) {
      fill(all(cnt), 0);
      fore (i, 0, n) nsa[i] = (sa[i] - k + n) % n, cnt[rk[i]]++;
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
    int l = 0, r = n - 1;
    fore (i, 0, sz(t)) {
      int p = l, q = r;
      for (int k = n; k > 0; k >>= 1) {
        while (p + k < r && at(p + k, i) < t[i]) p += k;
        while (q - k > l && t[i] < at(q - k, i)) q -= k;
      }
      l = (at(p, i) == t[i] ? p : p + 1);
      r = (at(q, i) == t[i] ? q : q - 1);
      if (at(l, i) != t[i] && at(r, i) != t[i] || l > r) return 0;
    }
    return r - l + 1;
  }
};