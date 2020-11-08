int sgn(ld x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

template <class T>
struct Point {
  typedef Point<T> P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  P operator + (const P &p) const { return P(x + p.x, y + p.y); }
  P operator - (const P &p) const { return P(x - p.x, y - p.y); }
  P operator * (T k) const { return P(x * k, y * k); }
  P operator / (T k) const { return P(x / k, y / k); }
  bool operator == (const P &p) const { return eq(x, p.x) && eq(y, p.y); }
  bool operator != (const P &p) const { return neq(x, p.x) || neq(y, p.y); }

  T dot(const P &p) { return x * p.x + y * p.y; }
  T cross(const P &p) { return x * p.y - y * p.x; }
  T norm() { return x * x + y * y; }
  double length() { return sqrtl(norm()); }
  double angle() { return atan2(y, x); }

  P perp() const { return P(-y, x); }
  P unit() const { return (*this) / length(); }
  P rotate(double angle) const {
    return P(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }

  friend ostream &operator << (ostream &os, const P &p) { return os << "(" << p.x << ", " << p.y << ")"; }
  friend istream &operator >> (istream &is, P &p) { return cin >> p.x >> p.y; }
};

using P = Point<double>;

double ccw(P a, P b, P c) { 
  return (b - a).cross(c - a); 
}
