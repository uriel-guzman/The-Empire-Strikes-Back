struct MinQueue : deque< pair<lli, int> > {
  // add a element to the right {val, pos}
  void add(lli val, int pos) { 
    while (!empty() && back().f >= val)
      pop_back();
    emplace_back(val, pos);
  }
  // remove all less than pos
  void rem(int pos) { 
    while (front().s < pos)
      pop_front();
  }

  lli qmin() { return front().f; }
};
