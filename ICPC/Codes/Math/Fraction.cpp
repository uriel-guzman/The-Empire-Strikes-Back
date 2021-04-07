struct Frac {
  lli n, d;
  Frac(lli a = 0, lli b = 1) {
    lli g = gcd(a, b);
    n = a / g, d = b / g;
    if (d < 0) n *= -1, d *= -1;
  }

  bool operator < (const Frac &f) const { return n * f.d < f.n * d; }
  bool operator > (const Frac &f) const { return n * f.d > f.n * d; }
  bool operator == (const Frac &f) const { return n == f.n && d == f.d; }
  bool operator != (const Frac &f) const { return n != f.n || d != f.d; }

  friend Frac abs(const Frac &f) { return Frac(abs(f.n), f.d); }
  friend ostream & operator << (ostream &os, const Frac &f) { return os << f.n << "/" << f.d; }

  Frac operator - () const { return Frac(-n, d); }
  double operator ()() const { return double(n) / double(d); }
  Frac operator * (const Frac &f) { return Frac(n * f.n, d * f.d); }
  Frac operator / (const Frac &f) { return Frac(n * f.d, d * f.n); }

  Frac operator + (const Frac &f) { 
    lli k = lcm(d, f.d);
    return Frac(n * (k / d) + f.n * (k / f.d), k); 
  }

  Frac operator - (const Frac &f) { 
    lli k = lcm(d, f.d);
    return Frac(n * (k / d) - f.n * (k / f.d), k); 
  }
};