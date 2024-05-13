// https://vjudge.net/problem/Aizu-DSL_2_C

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r)                                      \
  for (auto i = (l) - ((l) > (r)); i != (r) - ((l) > (r)); \
       i += 1 - 2 * ((l) > (r)))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

using ld = long double;
using lli = long long;
using ii = pair<int, int>;
using vi = vector<int>;

const ld EPS = 1e-20;
const ld INF = 1e18;
const ld PI = acos(-1.0);
enum { ON = -1, OUT, IN, OVERLAP };

#define eq(a, b) (abs((a) - (b)) <= +EPS)
#define neq(a, b) (!eq(a, b))
#define geq(a, b) ((a) - (b) >= -EPS)
#define leq(a, b) ((a) - (b) <= +EPS)
#define ge(a, b) ((a) - (b) > +EPS)
#define le(a, b) ((a) - (b) < -EPS)

int sgn(ld a) {
  return (a > EPS) - (a < -EPS);
}

struct Pt {
  int i;
  ld x, y;
  explicit Pt(ld x = 0, ld y = 0) : x(x), y(y) {}

  Pt operator+(Pt p) const {
    return Pt(x + p.x, y + p.y);
  }

  Pt operator-(Pt p) const {
    return Pt(x - p.x, y - p.y);
  }

  Pt operator*(ld k) const {
    return Pt(x * k, y * k);
  }

  Pt operator/(ld k) const {
    return Pt(x / k, y / k);
  }

  ld dot(Pt p) const {
    // 0 if vectors are orthogonal
    // - if vectors are pointing in opposite directions
    // + if vectors are pointing in the same direction
    return x * p.x + y * p.y;
  }

  ld cross(Pt p) const {
    // 0 if collinear
    // - if b is to the right of a
    // + if b is to the left of a
    // gives you 2 * area
    return x * p.y - y * p.x;
  }

  ld norm() const {
    return x * x + y * y;
  }

  ld length() const {
    return sqrtl(norm());
  }

  Pt unit() const {
    return (*this) / length();
  }

  ld angle() const {
    ld ang = atan2(y, x);
    return ang + (ang < 0 ? 2 * acos(-1) : 0);
  }

  Pt perp() const {
    return Pt(-y, x);
  }

  Pt rotate(ld angle) const {
    // counter-clockwise rotation in radians
    // degree = radian * 180 / pi
    return Pt(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
  }

  int dir(Pt a, Pt b) const {
    // where am I on the directed line ab
    return sgn((a - *this).cross(b - *this));
  }

  bool operator<(Pt p) const {
    return eq(x, p.x) ? le(y, p.y) : le(x, p.x);
  }

  bool operator==(Pt p) const {
    return eq(x, p.x) && eq(y, p.y);
  }

  bool operator!=(Pt p) const {
    return !(*this == p);
  }

  friend ostream& operator<<(ostream& os, const Pt& p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }

  friend istream& operator>>(istream& is, Pt& p) {
    return is >> p.x >> p.y;
  }

  ld operator[](int i) const {
    return i == 0 ? x : y;
  }
};

struct KDTree {
  Pt p;
  int k;
  KDTree *left, *right;

  template <class Iter>
  KDTree(Iter l, Iter r, int k = 0) : k(k), left(0), right(0) {
    int n = r - l;
    if (n == 1) {
      p = *l;
      return;
    }
    nth_element(l, l + n / 2, r, [&](Pt a, Pt b) { return a[k] < b[k]; });
    p = *(l + n / 2);
    left = new KDTree(l, l + n / 2, k ^ 1);
    right = new KDTree(l + n / 2, r, k ^ 1);
  }

  bool inRange(ld x, ld l, ld r) {
    return leq(l, x) && leq(x, r);
  }

  void within(Pt lo, Pt hi, vector<int>& st) {
    if (!left && !right) {
      if (inRange(p.x, lo.x, hi.x) && inRange(p.y, lo.y, hi.y))
        st.pb(p.i);
      return;
    }

    if (leq(lo[k], p[k]))
      left->within(lo, hi, st);
    if (leq(p[k], hi[k]))
      right->within(lo, hi, st);
  }
};

const int N = 5e5 + 5;
Pt pts[N];

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  int n, q;
  cin >> n;
  fore (i, 0, n) {
    cin >> pts[i];
    pts[i].i = i;
  }

  KDTree tree(pts, pts + n);

  cin >> q;
  while (q--) {
    Pt lo, hi;
    cin >> lo.x >> hi.x >> lo.y >> hi.y;

    vector<int> st;
    tree.within(lo, hi, st);

    sort(all(st));

    for (int i : st) cout << i << '\n';
    cout << '\n';
  }

  return 0;
}