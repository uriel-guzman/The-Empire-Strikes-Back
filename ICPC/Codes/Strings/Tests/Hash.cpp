#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r) for (auto i = (l) - ((l) > (r)); i != (r) - ((l) > (r)); i += 1 - 2 * ((l) > (r)))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

using ld = long double;
using lli = long long;
using ii = pair<int, int>;
using vi = vector<int>;

struct Random {
  mt19937 rng;

  Random() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

  // Fills a vector of type T using a generator to create a single element.
  template <class T, class Generator>
  vector<T> fillArray(int n, bool unique, Generator g) {
    assert(n >= 0);
    vector<T> v(n);
    if (unique) {
      for (auto& x : v)
        x = g();
    } else {
      set<T> st;
      for (auto& x : v) {
        do {
          x = g();
        } while (st.count(x));
        st.insert(x);
      }
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

  // Returns a string of size n following 'pattern'.
  // The 'pattern' needs a pair of elements, it could be multiple pairs, i.e. "acDF15" all strings will be of characters of the set
  // {[a,c],[D,F],[1,5]}
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

using Hash = int; // maybe an arrray<int, 2>
const int N = 1e5 + 5;
Hash pw[N], ipw[N];

lli inv(lli a, lli m) {
  a %= m;
  assert(a);
  return a == 1 ? 1 : m - 1LL * inv(m, a) * m / a;
}

struct Hashing {
  static constexpr int P = 10166249, M = 1070777777;
  vector<Hash> h;

  static void init() {
    const int Q = inv(P, M);
    pw[0] = ipw[0] = 1;
    fore (i, 1, N) {
      pw[i] = 1LL * pw[i - 1] * P % M;
      ipw[i] = 1LL * ipw[i - 1] * Q % M;
    }
  }

  Hashing(string& s) : h(sz(s) + 1, 0) {
    fore (i, 0, sz(s)) {
      lli x = s[i] - 'a' + 1;
      h[i + 1] = (h[i] + x * pw[i]) % M;
    }
  }

  Hash query(int l, int r) {
    return 1LL * (h[r + 1] - h[l] + M) * ipw[l] % M;
  }

  Hash full() {
    return h.back();
  }

  static pair<Hash, int> merge(vector<pair<Hash, int>>& cuts) {
    pair<Hash, int> ans = {0, 0};
    fore (i, sz(cuts), 0) {
      ans.f = (cuts[i].f + 1LL * ans.f * pw[cuts[i].s] % M) % M;
      ans.s += cuts[i].s;
    }
    return ans;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  Random random;
  Hashing::init();

  auto queryWorks = [&](int tests) {
    int n = 100;

    int bad = 0;
    fore (it, 0, tests) {
      auto str = random.getString(n, "az");
      Hashing hash(str);

      fore (l, 0, n) {
        string tmp = "";
        fore (r, l, n) {
          tmp += str[r];
          auto good = hash.query(l, r);
          auto brute = Hashing(tmp).full();
          if (good != brute) {
            bad++;
          }
        }
      }
    }

    cout << "Bad query results percentage: " << 100 * bad / double(tests) << " %\n";
  };

  auto mergeWorks = [&](int tests) {
    int n = 1000;
    int k = 100;

    int bad = 0;
    fore (it, 0, tests) {
      auto str = random.getString(n, "az");
      Hashing hash(str);

      string strMerged;
      vector<pair<Hash, int>> ranges;
      for (int l : random.getArray(k, 0, n - 1)) {
        int r = random.get<int>(l, n - 1);
        int len = r - l + 1;
        ranges.pb({hash.query(l, r), len});
        strMerged += str.substr(l, len);
      }

      auto good = Hashing::merge(ranges).f;
      auto good2 = hash.merge(ranges).f;
      auto brute = Hashing(strMerged).full();
      if (good != brute || good != good2) {
        bad++;
      }
    }

    cout << "Bad merge results percentage: " << 100 * bad / double(tests) << " %\n";
  };

  queryWorks(100);
  mergeWorks(1000);

  return 0;
}
