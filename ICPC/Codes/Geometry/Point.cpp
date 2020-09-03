int sgn(ld x) {
  return x > 0 ? 1 : (x < 0 ? -1 : 0);
}

template <class T>
struct Point {
  typedef Point<T> P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  P operator + (const P &p) const { 
    return P(x + p.x, y + p.y); }
  P operator - (const P &p) const { 
    return P(x - p.x, y - p.y); }
  P operator * (T k) const { 
    return P(x * k, y * k); }
  P operator / (T k) const { 
    return P(x / k, y / k); }

  T dot(const P &p) { return x * p.x + y * p.y; }
  T cross(const P &p) { return x * p.y - y * p.x; }
  double length() const { return sqrtl(norm()); }
  T norm() const { return sq(x) + sq(y); } // double ?
  double angle() { return atan2(y, x); }

  P perp() const { return P(-y, x); }
  P unit() const { return (*this) / length(); }
  P rotate (double angle) const {
    return P(x * cos(angle) - y * sin(angle), 
             x * sin(angle) + y * cos(angle)); }

  bool operator == (const P &p) const { 
    return eq(x, p.x) && eq(y, p.y); }
  bool operator != (const P &p) const { 
    return neq(x, p.x) || neq(y, p.y); }

  friend ostream & operator << (ostream &os, P &p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};
typedef Point<double> P;

double ccw(P a, P b, P c) {
  return (b - a).cross(c - a);
}
