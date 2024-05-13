struct Frac {
  lli num, den;

  Frac(lli a = 0, lli b = 1) {
    lli g = gcd(a, b);
    num = a / g, den = b / g;
    if (den < 0)
      num *= -1, den *= -1;
  }

  bool operator<(const Frac& f) const {
    return num * f.den < f.num * den;
  }

  bool operator==(const Frac& f) const {
    return num == f.num && den == f.den;
  }

  bool operator!=(const Frac& f) const {
    return !(*this == f);
  }

  friend Frac abs(const Frac& f) {
    return Frac(abs(f.num), f.den);
  }

  friend ostream& operator<<(ostream& os, const Frac& f) {
    return os << f.num << "/" << f.den;
  }

  Frac operator-() const {
    return Frac(-num, den);
  }

  double operator()() const {
    return double(num) / double(den);
  }

  Frac operator*(const Frac& f) {
    return Frac(num * f.num, den * f.den);
  }

  Frac operator/(const Frac& f) {
    return Frac(num * f.den, den * f.num);
  }

  Frac operator+(const Frac& f) {
    lli k = lcm(den, f.den);
    return Frac(num * (k / den) + f.num * (k / f.den), k);
  }

  Frac operator-(const Frac& f) {
    lli k = lcm(den, f.den);
    return Frac(num * (k / den) - f.num * (k / f.den), k);
  }
};