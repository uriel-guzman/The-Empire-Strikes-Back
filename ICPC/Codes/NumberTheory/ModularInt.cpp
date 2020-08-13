template <int mod>
struct Modular {
  int v;
  Modular(lli x = 0) : v(x % mod) {}

  Modular operator + (const Modular &m) const { return Modular(v + m.v); }
  Modular operator - (const Modular &m) const { return Modular(v - m.v + mod); }
  Modular operator * (const Modular &m) const { return Modular(1LL * v * m.v); }
  Modular inv() const { return Modular(minv(v, mod)); } 
  
  void operator += (const Modular &m) { *this = *this + m; }
  void operator -= (const Modular &m) { *this = *this - m; }
  void operator *= (const Modular &m) { *this = *this * m; }
  
  friend ostream & operator << (ostream &os, const Modular &m) { return os << m.v; }
  friend istream & operator >> (istream &os, const Modular &m) { return is >> m.v; }
  
private:
  static int minv(int a, int m) {
		a %= m;
		assert(a); // ensures this is valid
		return a == 1 ? 1 : int(m - lli(minv(m, a)) * lli(m) / a);
	}
};
