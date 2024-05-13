template <class T>
struct DisjointIntervals {
  set<pair<T, T>> st;

  void insert(T l, T r) {
    auto it = st.lower_bound({l, -1});
    if (it != st.begin() && l <= prev(it)->s)
      l = (--it)->f;
    for (; it != st.end() && it->f <= r; st.erase(it++)) r = max(r, it->s);
    st.insert({l, r});
  }

  void erase(T l, T r) {
    auto it = st.lower_bound({l, -1});
    if (it != st.begin() && l <= prev(it)->s)
      --it;
    T mn = l, mx = r;
    for (; it != st.end() && it->f <= r; st.erase(it++))
      mn = min(mn, it->f), mx = max(mx, it->s);
    if (mn < l)
      st.insert({mn, l - 1});
    if (r < mx)
      st.insert({r + 1, mx});
  }
};