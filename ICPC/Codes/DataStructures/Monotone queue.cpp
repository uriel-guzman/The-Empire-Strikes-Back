struct MonotoneQueue : deque<pair<lli, int>> {
  void add(lli val, int pos) {
    while (!empty() && back().f >= val) 
      pop_back();
    emplace_back(val, pos);
  }

  void remove(int pos) {
    while (front().s < pos)
      pop_front();
  }

  lli query() {
    return front().f;
  }
}; 