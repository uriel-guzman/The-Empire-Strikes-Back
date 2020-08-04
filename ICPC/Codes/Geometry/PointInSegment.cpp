bool pointInSegment(P a, P b, P p){
  return (b - a).cross(p - a) == 0 && (a - p).dot(b - p) <= 0;
}
