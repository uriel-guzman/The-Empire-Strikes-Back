int intersectLinesInfo (P a1, P v1, P a2, P v2) { // v1 = b - a, v2 = d - c
  if (v1.cross(v2) == 0)
    return (a2 - a1).cross(v1) == 0 ? -1 : 0; // -1: infinity Ps, 0: no Ps
  else
    return 1; // single P
}

P intersectLines (P a1, P v1, P a2, P v2) {
  return a1 + v1 * ((a2 - a1).cross(v2) / v1.cross(v2));
}
