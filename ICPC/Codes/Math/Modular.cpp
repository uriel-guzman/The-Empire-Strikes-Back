template <const int M>
struct Modular {
  int v;
  Modular(int a = 0) : v(a) {}
  Modular(lli a) : v(a % M) {
    if (v < 0)
      v += M;
  }

  Modular operator+(Modular m) {
    return Modular((v + m.v) % M);
  }

  Modular operator-(Modular m) {
    return Modular((v - m.v + M) % M);
  }

  Modular operator*(Modular m) {
    return Modular((1LL * v * m.v) % M);
  }

  Modular inv() {
    return this->pow(M - 2);
  }

  Modular operator/(Modular m) {
    return *this * m.inv();
  }

  Modular& operator+=(Modular m) {
    return *this = *this + m;
  }

  Modular& operator-=(Modular m) {
    return *this = *this - m;
  }

  Modular& operator*=(Modular m) {
    return *this = *this * m;
  }

  Modular& operator/=(Modular m) {
    return *this = *this / m;
  }

  friend ostream& operator<<(ostream& os, Modular m) {
    return os << m.v;
  }

  Modular pow(lli n) {
    Modular r(1), x = *this;
    for (; n > 0; n >>= 1) {
      if (n & 1)
        r = r * x;
      x = x * x;
    }
    return r;
  }
};
