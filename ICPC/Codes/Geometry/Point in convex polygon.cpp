bool contains(const vector<Pt> &a, Pt p) {
  int lo = 1, hi = sz(a) - 1;
  if (a[0].dir(a[lo], a[hi]) > 0) 
    swap(lo, hi);
  if (p.dir(a[0], a[lo]) >= 0 || p.dir(a[0], a[hi]) <= 0) 
    return false; 
  while (abs(lo - hi) > 1) {
    int mid = (lo + hi) >> 1;
    (p.dir(a[0], a[mid]) > 0 ? hi : lo) = mid;
  } 
  return p.dir(a[lo], a[hi]) < 0;
}