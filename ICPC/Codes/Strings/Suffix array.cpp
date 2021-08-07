template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, rank, sp[25]; 

  SuffixArray(const T &x) : n(sz(x) + 1), s(x), sa(n), rank(n) {
    s.pb(0);
    fore (i, 0, n) sa[i] = i, rank[i] = s[i];
    vector<int> nsa(n), cnt(max(260, n));
    for (int k = 0; k < n && rank[sa[n - 1]] != n - 1; k ? k *= 2 : k++) {
      fill(all(cnt), 0);
      fore (i, 0, n) nsa[i] = (sa[i] - k + n) % n, cnt[rank[i]]++;
      partial_sum(all(cnt), cnt.begin());
      fore (i, n, 0) sa[--cnt[rank[nsa[i]]]] = nsa[i];
      vector<int> prev(rank);
      for (int i = 1, r = 0; i < n; i++) {
        if (prev[sa[i]] != prev[sa[i - 1]] || prev[(sa[i] + k) % n] != prev[(sa[i - 1] + k) % n]) r++;
        rank[sa[i]] = r;
      }
    }
    sp[0].resize(n);
    for (int i = 0, j = rank[0], k = 0; i < n - 1; i++, k++) 
      while (k >= 0 && s[i] != s[sa[j - 1] + k])
        sp[0][j] = k--, j = rank[sa[j] + 1];  
    for (int k = 1; (1 << k) < n; k++) {
      sp[k].resize(n - (1 << k) + 1);
      fore (l, 0, n - (1 << (k - 1))) {
        int r = l + (1 << (k - 1)); 
        sp[k][l] = min(sp[k - 1][l], sp[k - 1][r]);
      }
    }
  }

  int lcp(int l, int r) { 
    int k = __lg(r - ++l + 1);
    return min(sp[k][l], sp[k][r - (1 << k) + 1]);
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

  bool compare(ii a, ii b) {
    // s[a.f ... a.s] < s[b.f ... b.s]
    ii range = minmax(rank[a.f], rank[b.f]);
    int common = lcp(range.f, range.s);
    int szA = a.s - a.f + 1, szB = b.s - b.f + 1;
    if (common >= min(szA, szB)) return szA < szB;
    return rank[a.f] < rank[b.f];
  }
};