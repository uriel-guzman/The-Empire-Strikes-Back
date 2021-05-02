template <class T, class F = less<T>>
struct MonotoneQueue {
  deque<pair<T, int>> cum;
  F f;

  void add(T val, int pos) {
    while (cum.size() && !f(cum.back().f, val)) 
      cum.pop_back();
    cum.emplace_back(val, pos);
  }

  void keep(int pos) {
    while (cum.size() && cum.front().s < pos) 
      cum.pop_front();
  }

  T query() {
    return cum.empty() ? T() : cum.front().f;
  }
}; 