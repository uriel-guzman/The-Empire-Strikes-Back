template <const int M>
struct Modular {
  int v;
  Modular(int v = 0) : v(v) {}
  Modular(int64_t v) : v(v % M) {}
    
  Modular operator + (Modular m) { return Modular((v + m.v) % M); };
  Modular operator - (Modular m) { return Modular((v - m.v + M) % M); };
  Modular operator * (Modular m) { return Modular((1LL * v * m.v) % M); };
  Modular operator / (Modular m) { return *this * m.inv(); };
  Modular inv() { return this->pow(M - 2); }
 
  friend ostream & operator << (ostream &os, const Modular &m) { return os << m.v; }
  template <class T> bool operator == (T x) { return v == x; }

  Modular pow(lli n) {
    Modular r(1), x = *this;
    for (; n > 0; n >>= 1) {
      if (n & 1) r = r * x;
      x = x * x;
    }
    return r;
  }
};