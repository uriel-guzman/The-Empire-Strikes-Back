struct Frac {
  bool operator < (const Frac &f) { 
    return n * f.d < f.n * d; 
  }

  bool operator > (const Frac &f) { 
    return n * f.d > f.n * d; 
  }

  bool operator == (const Frac &f) { 
    return n == f.n && d == f.d; 
  }

  bool operator != (const Frac &f) { 
    return n != f.n || d != f.d; 
  }

  Frac operator - () const { 
    return Frac(-n, d); 
  }

  Frac operator + (const Frac &f) { 
    lli k = lcm(d, f.d);
    return Frac(n * (k / d) + f.n * (k / f.d), k); 
  }

  Frac operator - (const Frac &f) { 
    lli k = lcm(d, f.d);
    return Frac(n * (k / d) - f.n * (k / f.d), k); 
  }

  Frac operator * (const Frac &f) { 
    return Frac(n * f.n, d * f.d); 
  }
  
  Frac operator / (const Frac &f) { 
    return Frac(n * f.d, d * f.n); 
  }

  friend Frac abs(const Frac &f) { 
    return Frac(abs(f.n), f.d); 
  }
  
  friend ostream & operator << (ostream &os, const Frac &f) {
    return os << f.n << "/" << f.d;
  }

  lli n, d;
  Frac(lli a = 0, lli b = 1) {
    lli g = __gcd(a, b);
    n = a / g, d = b / g;
    if (d < 0) n *= -1, d *= -1;
  }
};