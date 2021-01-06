int intersectLineSegmentInfo(P a, P v, P c, P d) {
  P v2 = d - c;
  ld det = v.cross(v2);
  if (det == 0) {
    if ((c - a).cross(v) == 0)
  	  return -1; // infinity points
  	else 
    	return 0; //no points
  } else
    	return sgn(v.cross(c - a)) != sgn(v.cross(d - a));
}
