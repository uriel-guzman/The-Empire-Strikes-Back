struct Pt {
  ld x, y;
  explicit Pt(ld x = 0, ld y = 0) : x(x), y(y) {}
  Pt operator + (Pt p) const { return Pt(x + p.x, y + p.y); }
  Pt operator - (Pt p) const { return Pt(x - p.x, y - p.y); }
  Pt operator * (ld k) const { return Pt(x * k, y * k); }
  Pt operator / (ld k) const { return Pt(x / k, y / k); }

  ld dot(Pt p) const { 
    // 0 if vectors are orthogonal
    // - if vectors are pointing in opposite directions
    // + if vectors are pointing in the same direction
    return x * p.x + y * p.y; 
  }

  ld cross(Pt p) const { 
    // 0 if collinear
    // - if b is to the right of a
    // + if b is to the left of a
    // gives you 2 * area 
    return x * p.y - y * p.x; 
  }
    
  ld norm() const { return x * x + y * y; }
  ld length() const { return sqrtl(norm()); }
  
  ld angle() const { 
    ld ang = atan2(y, x); 
    return ang + (ang < 0 ? 2 * acos(-1) : 0);
  }

  Pt perp() const { return Pt(-y, x); }
  Pt unit() const { return (*this) / length(); }
  Pt rotate(ld angle) const {
    // counter-clockwise rotation in radians
    // degree = radian * 180 / pi
    return Pt(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }

  int dir(Pt a, Pt b) const {
    // where am I on the line directed line ab
    return sgn((a - *this).cross(b - *this));
  }
  
  int cuad() const {
    if (x > 0 && y >= 0) return 0;
    if (x <= 0 && y > 0) return 1;
    if (x < 0 && y <= 0) return 2;
    if (x >= 0 && y < 0) return 3;
    return -1;
  }  

  bool operator == (Pt p) const { return eq(x, p.x) && eq(y, p.y); }
  bool operator != (Pt p) const { return neq(x, p.x) || neq(y, p.y); }
  
  friend ostream &operator << (ostream &os, const Pt &p) { 
    return os << "(" << p.x << ", " << p.y << ")"; 
  }
  
  friend istream &operator >> (istream &is, Pt &p) {
    return is >> p.x >> p.y;
  } 
};