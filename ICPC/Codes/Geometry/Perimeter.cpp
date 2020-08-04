double perimeter(vector<P> points){
  int n = sz(points);
  double sum = 0;
  fore (i, 0, n)
    sum += (points[(i + 1) % n] - points[i]).length();
  return sum;
}
