template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, pos, sp[25];

  SuffixArray(const T& x) : n(sz(x) + 1), s(x), sa(n), pos(n) {
    s.pb(0);
    fore (i, 0, n) sa[i] = i, pos[i] = s[i];
    vector<int> nsa(sa), npos(n), cnt(max(260, n), 0);
    for (int k = 0; k < n; k ? k *= 2 : k++) {
      fill(all(cnt), 0);
      fore (i, 0, n) 
        nsa[i] = (sa[i] - k + n) % n, cnt[pos[i]]++;
      partial_sum(all(cnt), cnt.begin());
      for (int i = n - 1; i >= 0; i--) 
        sa[--cnt[pos[nsa[i]]]] = nsa[i];
      for (int i = 1, cur = 0; i < n; i++) {
        cur += (pos[sa[i]] != pos[sa[i - 1]] ||
                pos[(sa[i] + k) % n] != pos[(sa[i - 1] + k) % n]);
        npos[sa[i]] = cur;
      }
      pos = npos;
      if (pos[sa[n - 1]] >= n - 1) break;
    }
    sp[0].assign(n, 0);
    for (int i = 0, j = pos[0], k = 0; i < n - 1; ++i, ++k) 
    {
      while (k >= 0 && s[i] != s[sa[j - 1] + k])
        sp[0][j] = k--, j = pos[sa[j] + 1];
    }
    for (int k = 1, pw = 1; pw < n; k++, pw <<= 1) {
      sp[k].assign(n, 0);
      for (int l = 0; l + pw < n; l++)
        sp[k][l] = min(sp[k - 1][l], sp[k - 1][l + pw]);
    }
  }

  int lcp(int l, int r) {
    if (l == r) return n - l;
    tie(l, r) = minmax(pos[l], pos[r]);
    int k = __lg(r - l);
    return min(sp[k][l + 1], sp[k][r - (1 << k) + 1]);
  }

  auto at(int i, int j) { 
    return sa[i] + j < n ? s[sa[i] + j] : 'z' + 1;
  }

  int count(T& t) {
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
    int common = lcp(a.f, b.f);
    int szA = a.s - a.f + 1, szB = b.s - b.f + 1;
    if (common >= min(szA, szB)) 
      return tie(szA, a) < tie(szB, b);
    return s[a.f + common] < s[b.f + common];
  }
};