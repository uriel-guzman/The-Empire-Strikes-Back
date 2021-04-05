template <class T, class F>
T lowerBound(T lo, T hi, F ok) {
	while (lo + 1 < hi) {
		T mid = (lo + hi) >> 1;
		if (ok(mid))
			hi = mid;
		else
			lo = mid;
	}
	return ok(lo) ? lo : ok(hi) ? hi : -1;
}
