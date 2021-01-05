P reflectionLine(P a, P v, P p){
  return a * 2 - p + proj(p - a, v) * 2;
}
