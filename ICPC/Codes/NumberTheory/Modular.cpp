template <int p>
struct Mod {
  Mod operator + (const Mod &m) const { return Mod(v + m.v); }
  Mod operator - (const Mod &m) const { return Mod(v - m.v + p); }
  Mod operator * (const Mod &m) const { return Mod(1LL * v * m.v); }
  Mod inv() const { return Mod(minv(v, p)); } 
  Mod operator - () const { return Mod(-v); }
  
  Mod& operator += (const Mod &m) { return *this = *this + m; }
  Mod& operator -= (const Mod &m) { return *this = *this - m; }
  Mod& operator *= (const Mod &m) { return *this = *this * m; }
  
  friend ostream & operator << (ostream &os, const Mod &m) { return os << m.v; }
  friend istream & operator >> (istream &is, Mod &m) { return is >> m.v; }
  
  int v;
  Mod(lli x = 0) : v((x %= p) < 0 ? x + p : x) {}
private:
  static int minv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - lli(minv(m, a)) * lli(m) / a);
  }
};
 
// for a variable modulo or normal one
using Mint = Mod<int(1e9) + 7>;