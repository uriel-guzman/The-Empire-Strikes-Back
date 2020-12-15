P projectionPointCircle(P c, ld r, P p){
	//point p (outside the circle), circle with center c and radius r
	return c + (p - c).unit() * r;
}
