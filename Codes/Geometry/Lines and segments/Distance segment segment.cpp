ld distance(Seg a, Seg b) {
  if (a.intersects(b)) return 0.L;
  return min({distance(a.a, b), distance(a.b, b), 
              distance(b.a, a), distance(b.b, a)});
}