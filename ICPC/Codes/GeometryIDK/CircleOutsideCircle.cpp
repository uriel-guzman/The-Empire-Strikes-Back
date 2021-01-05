int circleOutsideCircle(P c1, ld r1, P c2, ld r2) {
	//test if circle 2 is outside circle 1
	//returns "-1" if they touch externally, "1" if 2 is outside 1, "0" if they overlap
	ld l = (c1 - c2).length() - (r1 + r2);
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}
