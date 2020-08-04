template <class T>
struct MinQueue : deque< pair<T, int> > {
  // add a element to the right {val, pos}
  void add(T val, int pos) { 
    while (!empty() && back().f >= val)
      pop_back();
    emplace_back(val, pos);
  }
  // remove all less than pos
  void rem(int pos) { 
    while (front().s < pos)
      pop_front();
  }

  T qmin() { return front().f; }
};
