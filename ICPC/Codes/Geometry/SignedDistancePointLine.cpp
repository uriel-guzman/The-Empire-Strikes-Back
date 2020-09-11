double signedDistancePointLine(P a, P v, P p){
  return v.cross(p - a) / v.length();
}
