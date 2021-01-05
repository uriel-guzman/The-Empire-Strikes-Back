struct Circle {
  P c;
  ld r;
  Circle() {}
  Circle(const P &c, ld r) : c(c), r(r) {}
  set<pair<ld, ld>> ranges;

  void disable(ld l, ld r) { ranges.emplace(l, r); }

  auto getActive() const {
    vector<pair<ld, ld>> ans;
    ld maxi = 0;
    for (const auto& dis : ranges) {
      ld l, r;
      tie(l, r) = dis;
      if (l > maxi) {
        ans.emplace_back(maxi, l);
      }
      maxi = max(maxi, r);
    }
    if (!eq(maxi, 2 * pi)) {
      ans.emplace_back(maxi, 2 * pi);
    }
    return ans;
  }
};

ld areaUnionCircles(const vector<Circle>& circs) {
  vector<Circle> valid;
  for (const Circle& cur : circs) {
    if (eq(cur.r, 0)) continue;
    Circle nxt = cur;
    for (Circle& prev : valid) {
      if (circleInsideCircle(prev.c, prev.r, nxt.c, nxt.r)) {
        nxt.disable(0, 2 * pi);
      } else if (circleInsideCircle(nxt.c, nxt.r, prev.c, prev.r)) {
        prev.disable(0, 2 * pi);
      } else {
        auto intersection = intersectionCircles(prev.c, prev.r, nxt.c, nxt.r);
        if (intersection.size() == 2) {
          ld a1 = (intersection[0] - prev.c).ang();
          ld a2 = (intersection[1] - prev.c).ang();
          ld b1 = (intersection[1] - nxt.c).ang();
          ld b2 = (intersection[0] - nxt.c).ang();
          if (a1 < a2) {
            prev.disable(a1, a2);
          } else {
            prev.disable(a1, 2 * pi);
            prev.disable(0, a2);
          }
          if (b1 < b2) {
            nxt.disable(b1, b2);
          } else {
            nxt.disable(b1, 2 * pi);
            nxt.disable(0, b2);
          }
        }
      }
    }
    valid.push_back(nxt);
  }
  ld ans = 0;
  for (const Circle& cur : valid) {
    for (const auto& range : cur.getActive()) {
      ld l, r;
      tie(l, r) = range;
      ans += cur.r * (cur.c.x * (sin(r) - sin(l)) - cur.c.y * (cos(r) - cos(l))) + cur.r * cur.r * (r - l);
    }
  }
  return ans / 2;
};