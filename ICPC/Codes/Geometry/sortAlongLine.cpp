void sortAlongLine(vector<Pt> &pts, Line l){
  sort(all(pts), [&](Pt a, Pt b){
    return a.dot(l.v) < b.dot(l.v);
  });
}
