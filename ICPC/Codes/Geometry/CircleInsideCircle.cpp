int circleInsideCircle(P c1, ld r1, P c2, ld r2) {
	//test if circle 2 is inside circle 1
	//returns "-1" if 2 touches internally 1, "1" if 2 is inside 1, "0" if they overlap
	ld l = r1 - r2 - (c1 - c2).length();
	return (ge(l, 0) ? 1 : (eq(l, 0) ? -1 : 0));
}
