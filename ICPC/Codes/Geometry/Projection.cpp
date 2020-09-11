P proj(P a, P v){
  v = v / v.unit();
  return v * a.dot(v);
}
    