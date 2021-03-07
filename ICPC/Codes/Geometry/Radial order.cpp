struct Radial {
  Pt c;
  Radial(Pt c) : c(c) {}

  bool operator()(Pt a, Pt b) const {
    Pt p = a - c, q = b - c;
    if (p.cuad() == q.cuad()) 
      return p.y * q.x < p.x * q.y;
    return p.cuad() < q.cuad();
  }
};