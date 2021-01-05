void sortAlongLine(P a, P v, vector<P> & pts){
  sort(pts.begin(), pts.end(), [&](P u, P w){
    return u.dot(v) < w.dot(v);
  });
}
