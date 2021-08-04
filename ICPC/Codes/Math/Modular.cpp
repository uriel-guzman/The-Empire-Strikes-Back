template <const int M>
struct Modular {
  int v;
  Modular(int v = 0) : v(v) {}
  Modular(int64_t v = 0) : v(v % M) {}
    
  Modular operator + (Modular m) { return Modular((v + m.v) % M); };
  Modular operator - (Modular m) { return Modular((v - m.v + M) % M); };
  Modular operator * (Modular m) { return Modular((1LL * v * m.v) % M); };
  Modular operator / (Modular m) { return *this * m.inv(); };
  Modular inv() { return Modular(minv(v, M)); }
 
  friend ostream & operator << (ostream &os, const Modular &m) { return os << m.v; }
  template <class T> bool operator == (T x) { return v == x; }
private:
  static int minv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - lli(minv(m, a)) * lli(m) / a);
  }
};