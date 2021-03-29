template <class T>
struct MonotoneQueue {
  deque<pair<T, int>> q;

  void add(T val, int pos) {
    while (!q.empty() && q.back().f >= val) q.pop_back();
    q.emplace_back(val, pos);
  }

  void remove(int pos) {
    while (q.front().s < pos) q.pop_front();
  }

  T query() {
    return q.front().f;
  }
}; 