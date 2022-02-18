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
