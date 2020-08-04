void sort_along_line(P a, P v, vector<P> & Ps){
  sort(Ps.begin(), Ps.end(), [](P u, P w){
    return u.dot(v) < w.dot(v);
  });
}
