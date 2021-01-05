vector<ii> antipodalPairs(vector<P> &pts) {
	vector<ii> ans;
	int n = sz(pts), k = 1;
	auto f = [&](int u, int v, int w) { 
    return abs((pts[v % n] - pts[u % n]).cross(pts[w % n] - pts[u % n])); 
  };
	while (ge(f(n - 1, 0, k + 1), f(n - 1, 0, k)))
    ++k;
	for (int i = 0, j = k; i <= k && j < n; ++i) {
		ans.emplace_back(i, j);
		while (j < n - 1 && ge(f(i, i + 1, j + 1), f(i, i + 1, j)))
			ans.emplace_back(i, ++j);
	}
	return ans;
}
