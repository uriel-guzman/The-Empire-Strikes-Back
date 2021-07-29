template <int p>
struct Modular {
  int v;
  Modular(int64_t x = 0) : v(x % p) {
    if (x < 0) v += p;
  }
 
  Modular operator + (const Modular &m) const { return v + m.v; }
  Modular operator - (const Modular &m) const { return v - m.v; }
  Modular operator * (const Modular &m) const { return 1LL * v * m.v; }
  Modular inv() const { return minv(v, p); } 
  
  Modular& operator += (const Modular &m) { return *this = *this + m; }
  Modular& operator -= (const Modular &m) { return *this = *this - m; }
  Modular& operator *= (const Modular &m) { return *this = *this * m; }
  
  friend ostream & operator << (ostream &os, const Modular &m) { return os << m.v; }
private:
  static int minv(int a, int m) {
    return a %= m, assert(a), a == 1 ? 1 : int(m - lli(minv(m, a)) * lli(m) / a);
  }
};