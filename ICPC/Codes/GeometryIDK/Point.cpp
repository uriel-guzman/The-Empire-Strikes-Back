int sgn(ld x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

struct P {
  ld x, y;
  explicit P(ld x = 0, ld y = 0) : x(x), y(y) {}
  P operator + (const P &p) const { return P(x + p.x, y + p.y); }
  P operator - (const P &p) const { return P(x - p.x, y - p.y); }
  P operator * (ld k) const { return P(x * k, y * k); }
  P operator / (ld k) const { return P(x / k, y / k); }

  ld dot(const P &p) const { 
    // 0 if vectors are orthogonal
    // - if vectors are pointing in opposite directions
    // + if vectors are pointing in the same direction
    return x * p.x + y * p.y; 
  }
  ld cross(const P &p) const { 
    // 0 if collinear
    // - if b is to the right of a
    // + if b is to the left of a
    // gives you 2 * area 
    return x * p.y - y * p.x; 
  }
  ld norm() const { return x * x + y * y; }
  ld length() const { return sqrtl(norm()); }
  ld angle() { return atan2(y, x); }

  P perp() const { return P(-y, x); }
  P unit() const { return (*this) / length(); }
  P rotate(ld angle) const {
    return P(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }

  bool operator == (const P &p) const { return eq(x, p.x) && eq(y, p.y); }
  bool operator != (const P &p) const { return neq(x, p.x) || neq(y, p.y); }
  friend ostream &operator << (ostream &os, const P &p) { return os << "(" << p.x << ", " << p.y << ")"; }
  friend istream &operator >> (istream &is, P &p) { return cin >> p.x >> p.y; }

  int cuad() const {
    if (x > 0 && y >= 0) return 0;
    if (x <= 0 && y > 0) return 1;
    if (x < 0 && y <= 0) return 2;
    if (x >= 0 && y < 0) return 3;
    assert(x == 0 && y == 0);
    return -1;
  }
};

ld ccw(P a, P b, P c) { 
  return (b - a).cross(c - a); 
}
