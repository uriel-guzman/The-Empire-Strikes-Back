template <int mod>
struct Modular {
  int v;
  Modular(lli x = 0) : v(x % mod) {}
  Modular operator + (const Modular &m) const { return Modular(v + m.v); }
  Modular operator - (const Modular &m) const { return Modular(v - m.v + mod); }
  Modular operator * (const Modular &m) const { return Modular(1LL * v * m.v); }
  void operator += (const Modular &m) { *this = *this + m; }
  void operator -= (const Modular &m) { *this = *this - m; }
  void operator *= (const Modular &m) { *this = *this * m; }
};