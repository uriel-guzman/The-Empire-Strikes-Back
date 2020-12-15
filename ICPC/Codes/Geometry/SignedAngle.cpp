ld signed_angle(P a, P b) {
	return sgn(a.cross(b)) * acosl(a.dot(b) / (a.length() * b.length()));
}
