vector<P> intersectionCircles(P c1, ld r1, P c2, ld r2) {
	//circle 1 with center c1 and radius r1
	//circle 2 with center c2 and radius r2
	P d = c2 - c1;
	ld d2 = d.norm();
	if (eq(d2, 0)) 
    return {}; //concentric circles
	ld pd = (d2 + r1 * r1 - r2 * r2) / 2;
	ld h2 = r1 * r1 - pd * pd / d2;
	P p = c1 + d * pd / d2;
	if (eq(h2, 0)) 
    return {p}; //circles touch at one point
	else if (le(h2, 0)) 
    return {}; //circles don't intersect
	else {
		P u = d.perp() * sqrt(h2 / d2);
		return {p - u, p + u};
	}
}
