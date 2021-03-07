const ld eps = 1e-20;
#define eq(a, b) (abs((a) - (b)) <= +eps)
#define neq(a, b) (!eq(a, b))
#define geq(a, b) ((a) - (b) >= -eps)
#define leq(a, b) ((a) - (b) <= +eps)
#define ge(a, b) ((a) - (b) > +eps)
#define le(a, b) ((a) - (b) < -eps) 

enum {ON = -1, OUT, IN, OVERLAP, INF};
