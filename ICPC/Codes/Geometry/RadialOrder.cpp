struct Radial {
  Pt c;
  Radial(Pt c) : c(c) {}

  bool cmp(Pt a, Pt b) {
    if (a.cuad() == b.cuad()) 
      return a.y * b.x < a.x * b.y;
    return a.cuad() < b.cuad();
  }

  bool operator()(Pt a, Pt b) const {
    return cmp(a - c, b - c);
  }
};