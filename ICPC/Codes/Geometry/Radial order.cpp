struct Radial {
  Pt c;
  Radial(Pt c) : c(c) {}

  int cuad(Pt p) const {
    if (p.x > 0 && p.y >= 0) return 0;
    if (p.x <= 0 && p.y > 0) return 1;
    if (p.x < 0 && p.y <= 0) return 2;
    if (p.x >= 0 && p.y < 0) return 3;
    return -1;
  }  

  bool operator()(Pt a, Pt b) const {
    Pt p = a - c, q = b - c;
    if (cuad(p) == cuad(q)) 
      return p.y * q.x < p.x * q.y;
    return cuad(p) < cuad(q);
  }
};