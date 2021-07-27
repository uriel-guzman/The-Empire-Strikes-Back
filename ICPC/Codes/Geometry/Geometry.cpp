const ld EPS = 1e-20;
const ld INF = 1e18;
const ld PI = acos(-1.0);
enum {ON = -1, OUT, IN, OVERLAP};

#define eq(a, b) (abs((a) - (b)) <= +EPS)
#define neq(a, b) (!eq(a, b))
#define geq(a, b) ((a) - (b) >= -EPS)
#define leq(a, b) ((a) - (b) <= +EPS)
#define ge(a, b) ((a) - (b) > +EPS)
#define le(a, b) ((a) - (b) < -EPS) 

int sgn(ld a) { 
  return (a > EPS) - (a < -EPS); 
}
