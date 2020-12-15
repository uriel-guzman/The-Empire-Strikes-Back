vector<P> intersectLineCircle(P a, P v, P c, ld r) {
  P p = proj_line(a, v, c);
  ld d = (p - c).length();
  ld h = sq(r) - sq(d);
  if (h == 0) 
		return {p}; //line tangent to circle
  else if (h < 0) 
		return {}; //no intersection
  else {
    P u = v.unit() * sqrt(h);
    return {p - u, p + u}; //two Ps of intersection (chord)
  }
}
