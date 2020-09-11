double perimeter(vector<P> &pts){
  int n = sz(pts);
  double sum = 0;
  fore (i, 0, n)
    sum += (pts[(i + 1) % n] - pts[i]).length();
  return sum;
}
