bool pointInLine(P a, P v, P p) {
	//line a+tv, point p
	return eq((p - a).cross(v), 0);
}
