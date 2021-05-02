template <class T, int ...N> 
struct Fenwick {
  T v = T();
  void update(T v) { this->v += v; }
  T query() { return v; }  
};

template <class T, int N, int ...M>
struct Fenwick<T, N, M...> {
  #define lsb(x) (x & -x)
  Fenwick<T, M...> fenw[N + 1];

  template <typename... Args>
  void update(int i, Args... args) {
    for (; i <= N; i += lsb(i))
      fenw[i].update(args...);
  } 

  template <typename... Args>
  T query(int l, int r, Args... args) {
    T v = 0;
    for (; r > 0; r -= lsb(r))
      v += fenw[r].query(args...);
    for (--l; l > 0; l -= lsb(l))
      v -= fenw[l].query(args...);
    return v;
  }
};

// Fenwick<lli, 10, 20, 30>  is a 3D Fenwick<lli> of 10 * 20 * 30