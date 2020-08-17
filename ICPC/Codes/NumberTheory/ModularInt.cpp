template <int mod>
struct Modular {
  int v;
  Modular(lli x = 0) : v(-mod < x && x < mod ? x : x % mod) {
    if (v < 0) v += mod;
    if (v >= mod) v -= mod;
  }

  Modular operator + (const Modular &m) const { return Modular(v + m.v); }
  Modular operator - (const Modular &m) const { return Modular(v - m.v + mod); }
  Modular operator * (const Modular &m) const { return Modular(1LL * v * m.v); }
  Modular inv() const { return Modular(minv(v, mod)); } 
  
  Modular& operator += (const Modular &m) { return *this = *this + m; }
  Modular& operator -= (const Modular &m) { return *this = *this - m; }
  Modular& operator *= (const Modular &m) { return *this = *this * m; }
  
  friend ostream & operator << (ostream &os, const Modular &m) { return os << m.v; }
  friend istream & operator >> (istream &is, Modular &m) { return is >> m.v; }
  
private:
  static int minv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - lli(minv(m, a)) * lli(m) / a);
  }
};