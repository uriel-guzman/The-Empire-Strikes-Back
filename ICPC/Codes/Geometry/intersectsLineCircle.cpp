vector<P> intersectLineCircle(P a, P v, P c, double r){
  P p = proj_line(a, v, c);
  double d = (p - c).length();
  double h = sq(r) - sq(d);
  if(h == 0) 
		return {p}; //line tangent to circle
  else if(h < 0) 
		return {}; //no intersection
  else {
    P u = v.unit() * sqrt(h);
    return {p - u, p + u}; //two Ps of intersection (chord)
  }
}
