bool pointInLine(P a, P v, P p) {
  // line a + tv, point p, 
  // a, b are points that lie on the line, v = (b - a).unit()
  return eq((p - a).cross(v), 0);
}