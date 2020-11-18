double area(vector<P> &pts) {
  double sum = 0;
  fore (i, 0, sz(pts))
    sum += pts[i].cross(pts[(i + 1) % sz(pts)]);
  return abs(sum / 2);
}
