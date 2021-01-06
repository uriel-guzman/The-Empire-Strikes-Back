P projLine(P a, P v, P p){
  return a + proj(p - a, v);
}
