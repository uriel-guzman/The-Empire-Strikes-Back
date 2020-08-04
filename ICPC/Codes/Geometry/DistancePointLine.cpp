double distance_P_line(P a, P v, P p){
  return (proj(p - a, v) - (p - a)).length();
}
