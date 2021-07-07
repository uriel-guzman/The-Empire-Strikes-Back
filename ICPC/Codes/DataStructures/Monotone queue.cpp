template <class T, class F = less<T>>
struct MonotoneQueue {
  deque<pair<T, int>> pref;
  F f;

  void add(int pos, T val) {
    while (pref.size() && !f(pref.back().f, val)) 
      pref.pop_back();
    pref.emplace_back(val, pos);
  }

  void keep(int pos) { // >= pos
    while (pref.size() && pref.front().s < pos) 
      pref.pop_front();
  }

  T query() {
    return pref.empty() ? T() : pref.front().f;
  }
}; 