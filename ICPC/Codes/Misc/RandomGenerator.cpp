struct Random {
  mt19937 rng;

  Random() : rng(chrono::steady_clock::now().time_since_epoch().count()) {}

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

  template <class T, class Z = T>
  Z get(T low, Z high) {
    assert(low <= high);
    if constexpr (is_integral_v<Z>) {
      return uniform_int_distribution<Z>(low, high)(rng);
    } else if (is_floating_point_v<Z>) {
      return uniform_real_distribution<Z>(low, high)(rng);
    }
  }

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

  string getString(int size, string pattern = "az") {
    sort(pattern.begin(), pattern.end());
    assert(pattern.size());
    assert(size >= 0);
    string s;
    while (size--) {
      int k = rng() % (pattern.size() / 2);
      s += get<char>(pattern[2 * k], pattern[min<int>(2 * k + 1, pattern.size() - 1)]);
    }
    return s;
  }
};