#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r) for (auto i = (l) - ((l) > (r)); i != (r) - ((l) > (r)); i += 1 - 2 * ((l) > (r)))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

#ifdef LOCAL
#include "../../Misc/Debug.h"
#else
#define debug(...)
#endif

using ld = long double;
using lli = long long;
using ii = pair<int, int>;
using vi = vector<int>;

struct Result {
  lli total = 0, cnt = 0;

  void operator+=(bool flag) {
    total++;
    if (flag)
      cnt++;
  }

  Result inv() {
    Result copy = *this;
    copy.cnt = copy.total - copy.cnt;
    return copy;
  }

  friend ostream& operator<<(ostream& os, const Result& result) {
    return os << fixed << setprecision(2) << 100.0 * double(result.cnt) / double(result.total) << "%";
  }
};

struct Random {
  mt19937 rng;

  Random() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

  // Fills a vector of type T using a generator to create a single element.
  template <class T, class Generator>
  vector<T> fillArray(int n, bool unique, Generator g) {
    assert(n >= 0);
    vector<T> v(n);
    if (unique) {
      set<T> st;
      for (auto& x : v) {
        do {
          x = g();
        } while (st.count(x));
        st.insert(x);
      }
    } else {
      for (auto& x : v)
        x = g();
    }
    return v;
  }

  // Returns a random value, the default type is of the largest.
  template <class T, class Z = T>
  Z get(T low, Z high) {
    assert(low <= high);
    if constexpr (is_integral_v<Z>) {
      return uniform_int_distribution<Z>(low, high)(rng);
    } else if (is_floating_point_v<Z>) {
      return uniform_real_distribution<Z>(low, high)(rng);
    }
  }

  // Returns a vector of size n, with all elements in the range [low, high].
  template <class T>
  vector<T> getArray(int n, T low, T high, bool unique = false) {
    if (unique)
      if constexpr (is_integral_v<T>) {
        assert(high - low + 1 >= n);
      }
    return fillArray<T>(n, unique, [&]() {
      return get<T>(low, high);
    });
  }

  // Returns a vector of strings of size n, with all strings following 'pattern' and of sizes ranging from [minLength, maxLength].
  vector<string> getStrings(int n, string pattern = "az", int minLength = 1, int maxLength = 10, bool unique = false) {
    if (unique) {
      // assert that is possible to generate n different strings
      int letters = 0;
      for (int i = 0; i < pattern.size(); i += 2)
        letters += pattern[min<int>(i + 1, pattern.size() - 1)] - pattern[i] + 1;
      long long ways = 1;
      for (int length = minLength; length <= maxLength && ways < n; length++) {
        ways *= letters;
      }
      assert(ways >= n);
    }

    return fillArray<string>(n, unique, [&]() {
      int length = get<int>(minLength, maxLength);
      return getString(length, pattern);
    });
  }

  // Returns a string of size n following 'pattern'. The 'pattern' needs a pair of elements, it could be multiple pairs, i.e. "acDF15" all strings
  // will be of characters of the set {[a,c],[D,F],[1,5]}
  string getString(int n, string pattern = "az") {
    assert(pattern.size());
    assert(n >= 0);
    string s;
    while (n--) {
      int k = rng() % (pattern.size() / 2);
      s += get<char>(pattern[2 * k], pattern[min<int>(2 * k + 1, pattern.size() - 1)]);
    }
    return s;
  }

  template <class W>
  struct Edge {
    int from, to;
    W weight;

    bool operator<(const Edge& other) const {
      return set<int>({from, to}) < set<int>({other.from, other.to});
    }
  };

  // Creates a graph with weights in range [low, high].
  template <class T>
  vector<Edge<T>> getGraph(int numNodes, int numEdges, T low = 1, T high = 1, bool uniqueEdges = false) {
    if (uniqueEdges) {
      long long maxNumEdges = 1LL * numNodes * (numNodes - 1) / 2LL;
      assert(numEdges <= maxNumEdges);
    }
    return fillArray<Edge<T>>(numEdges, uniqueEdges, [&]() {
      Edge<T> edge;
      auto myPair = getArray<int>(2, 1, numNodes, true);
      edge.from = myPair[0];
      edge.to = myPair[1];
      edge.weight = get<T>(low, high);
      return edge;
    });
  }

  // Creates a tree with weights in range [low, high].
  template <class T>
  vector<Edge<T>> getTree(int numNodes, T low = 1, T high = 1) {
    int current = 2;
    return fillArray<Edge<T>>(numNodes - 1, true, [&]() {
      Edge<T> edge;
      edge.from = get<int>(1, current - 1);
      edge.to = current++;
      edge.weight = get<T>(low, high);
      return edge;
    });
  }
};

template <class T>
struct SuffixArray {
  int n;
  T s;
  vector<int> sa, pos, dp[25];

  SuffixArray(const T& x) : n(sz(x) + 1), s(x), sa(n), pos(n) {
    s.pb(0);
    fore (i, 0, n)
      sa[i] = i, pos[i] = s[i];
    vector<int> nsa(sa), npos(n), cnt(max(260, n), 0);
    for (int k = 0; k < n; k ? k *= 2 : k++) {
      fill(all(cnt), 0);
      fore (i, 0, n)
        nsa[i] = (sa[i] - k + n) % n, cnt[pos[i]]++;
      partial_sum(all(cnt), cnt.begin());
      for (int i = n - 1; i >= 0; i--)
        sa[--cnt[pos[nsa[i]]]] = nsa[i];
      for (int i = 1, cur = 0; i < n; i++) {
        cur += (pos[sa[i]] != pos[sa[i - 1]] || pos[(sa[i] + k) % n] != pos[(sa[i - 1] + k) % n]);
        npos[sa[i]] = cur;
      }
      pos = npos;
      if (pos[sa[n - 1]] >= n - 1)
        break;
    }
    dp[0].assign(n, 0);
    for (int i = 0, j = pos[0], k = 0; i < n - 1; ++i, ++k) {
      while (k >= 0 && s[i] != s[sa[j - 1] + k])
        dp[0][j] = k--, j = pos[sa[j] + 1];
    }
    for (int k = 1, pw = 1; pw < n; k++, pw <<= 1) {
      dp[k].assign(n, 0);
      for (int l = 0; l + pw < n; l++)
        dp[k][l] = min(dp[k - 1][l], dp[k - 1][l + pw]);
    }
  }

  int lcp(int l, int r) {
    if (l == r)
      return n - l;
    tie(l, r) = minmax(pos[l], pos[r]);
    int k = log2(r - l);
    return min(dp[k][l + 1], dp[k][r - (1 << k) + 1]);
  }

  auto at(int i, int j) {
    return sa[i] + j < n ? s[sa[i] + j] : 'z' + 1;
  }

  int count(T& t) {
    int l = 0, r = n - 1;
    fore (i, 0, sz(t)) {
      int p = l, q = r;
      for (int k = n; k > 0; k >>= 1) {
        while (p + k < r && at(p + k, i) < t[i])
          p += k;
        while (q - k > l && t[i] < at(q - k, i))
          q -= k;
      }
      l = (at(p, i) == t[i] ? p : p + 1);
      r = (at(q, i) == t[i] ? q : q - 1);
      if (at(l, i) != t[i] && at(r, i) != t[i] || l > r)
        return 0;
    }
    return r - l + 1;
  }

  bool less(ii a, ii b) {
    // s[a.f ... a.s] < s[b.f ... b.s]
    int common = lcp(a.f, b.f);
    int szA = a.s - a.f + 1, szB = b.s - b.f + 1;
    if (common >= min(szA, szB))
      return tie(szA, a) < tie(szB, b);
    return s[a.f + common] < s[b.f + common];
  }

  bool equal(ii a, ii b) {
    int common = lcp(a.f, b.f);
    int szA = a.s - a.f + 1, szB = b.s - b.f + 1;
    return common >= min(szA, szB);
  }
};

static Random gen;

pair<vector<string>, vector<int>> allCuts(string& str) {
  vector<int> order;
  vector<string> cuts;
  fore (i, 0, str.size()) {
    cuts.push_back(str.substr(i));
    order.emplace_back(i);
  }
  return {cuts, order};
}

void testSuffixArray() {
  Result result;
  fore (it, 0, 10000) {
    auto str = gen.getString(1000, "az");
    SuffixArray sa(str);

    vector<string> cuts;
    vector<int> order;
    tie(cuts, order) = allCuts(str);

    sort(all(order), [&](int i, int j) {
      return cuts[i] < cuts[j];
    });

    fore (i, 1, sa.sa.size()) {
      if (sa.sa[i] != order[i - 1]) {
        debug(sa.sa[i], order[i - 1]);
        result += 1;
      } else {
        result += 0;
      }
    }
  }

  cout << result.inv() << '\n';
}

void testAt() {
  Result result;
  fore (it, 0, 500) {
    auto str = gen.getString(100, "az");

    SuffixArray sa(str);

    auto cuts = allCuts(str).first;
    sort(all(cuts));

    fore (i, 1, sa.sa.size()) {
      int length = str.size() - sa.sa[i];
      result += (length == cuts[i - 1].size());
      fore (pos, 0, length) {
        result += (sa.at(i, pos) == cuts[i - 1][pos]);
      }
    }
  }

  cout << result << '\n';
}

void testCompare() {
  Result result;
  fore (it, 0, 100) {
    auto str = gen.getString(100, "az");
    SuffixArray sa(str);

    auto cuts = allCuts(str).first;
    sort(all(cuts));

    vector<ii> ranges;
    vector<int> order;
    fore (l, 0, str.size())
      fore (r, l, str.size()) {
        ranges.emplace_back(l, r);
        order.emplace_back(order.size());
      }

    for (auto [l, r] : ranges) {
      shuffle(all(order), gen.rng);

      fore (it, 0, 100) {
        auto [l2, r2] = ranges[order[it]];

        result += sa.compare(l, r)
      }
    }
  }

  cout << result << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  // testSuffixArray();
  // testAt();
  testCompare();

  return 0;
}

/* Please, check the following:
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * write down your ideas
 * DON'T get stuck on ONE APPROACH!
 * ASK for HELP from your TEAMMATES
 */