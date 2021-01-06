int sgn(ld x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

struct Pt {
  ld x, y;
  explicit Pt(ld x = 0, ld y = 0) : x(x), y(y) {}
  Pt operator + (const Pt &p) const { return Pt(x + p.x, y + p.y); }
  Pt operator - (const Pt &p) const { return Pt(x - p.x, y - p.y); }
  Pt operator * (ld k) const { return Pt(x * k, y * k); }
  Pt operator / (ld k) const { return Pt(x / k, y / k); }

  ld dot(const Pt &p) const { 
    // 0 if vectors are orthogonal
    // - if vectors are pointing in opposite directions
    // + if vectors are pointing in the same direction
    return x * p.x + y * p.y; 
  }

  ld cross(const Pt &p) const { 
    // 0 if collinear
    // - if b is to the right of a
    // + if b is to the left of a
    // gives you 2 * area 
    return x * p.y - y * p.x; 
  }
  
  ld norm() const { return x * x + y * y; }
  ld length() const { return sqrtl(norm()); }
  
  ld angle() { 
    ld ang = atan2(y, x); 
    return ang + (ang < 0 ? 2 * pi : 0);
  }

  Pt perp() const { return Pt(-y, x); }
  Pt unit() const { return (*this) / length(); }
  Pt rotate(ld angle) const {
    // counter-clockwise rotation in radians
    // degree = radian * 180 / pi
    return Pt(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }

  bool operator == (const Pt &p) const { return eq(x, p.x) && eq(y, p.y); }
  bool operator != (const Pt &p) const { return neq(x, p.x) || neq(y, p.y); }
  friend ostream &operator << (ostream &os, const Pt &p) { return os << "(" << p.x << ", " << p.y << ")"; }
  friend istream &operator >> (istream &is, Pt &p) { return cin >> p.x >> p.y; }

  int cuad() const {
    if (x > 0 && y >= 0) return 0;
    if (x <= 0 && y > 0) return 1;
    if (x < 0 && y <= 0) return 2;
    if (x >= 0 && y < 0) return 3;
    assert(x == 0 && y == 0);
    return -1;
  }
};

ld ccw(Pt a, Pt b, Pt c) { 
  return (b - a).cross(c - a); 
}
