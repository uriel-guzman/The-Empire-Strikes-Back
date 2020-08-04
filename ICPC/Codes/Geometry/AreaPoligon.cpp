double area(vector<P> &p) {
  double sum = 0;
  fore (i, 0, n)
    sum += p[i].cross(p[(i + 1) % sz(p)]);
  return abs(sum / 2);
}
