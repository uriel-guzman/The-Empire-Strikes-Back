ld perimeter(const vector<Pt>& pts) {
  ld sum = 0;
  fore (i, 0, sz(pts))
    sum += (pts[(i + 1) % sz(pts)] - pts[i]).length();
  return sum;
}
