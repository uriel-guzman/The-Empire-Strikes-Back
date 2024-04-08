// MonotoneQueue<int, greater<int>> = Max-MonotoneQueue
template <class T, class F = less<T>>
struct MonotoneQueue {
  deque<pair<T, int>> q;
  F f;

  void add(int pos, T val) {
    while (q.size() && !f(q.back().f, val)) q.pop_back();
    q.emplace_back(val, pos);
  }

  void trim(int pos) { // >= pos
    while (q.size() && q.front().s < pos) q.pop_front();
  }

  T query() { return q.empty() ? T() : q.front().f; }
};