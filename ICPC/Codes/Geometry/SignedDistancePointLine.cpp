double signed_distance_P_line(P a, P v, P p){
  return v.cross(p - a) / v.length();
}
