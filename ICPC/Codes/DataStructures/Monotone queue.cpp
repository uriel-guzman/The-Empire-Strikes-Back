template <class T, class F = less<T>>
struct MonotoneQueue : deque<pair<T, int>> {
  F f;

  void add(T val, int pos) {
    while (this->size() && !f(this->back().f, val)) 
      this->pop_back();
    this->emplace_back(val, pos);
  }

  void keep(int pos) {
    while (this->size() && this->front().s < pos) 
      this->pop_front();
  }

  T query() {
    return this->empty() ? 0 : this->front().f;
  }
}; 