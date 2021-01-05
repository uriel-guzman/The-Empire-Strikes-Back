void polarSort(vector<P> &P, P o, P v){
	//sort points in P around o, taking the direction of v as first angle
	sort(all(P), [&](P a, P b){
		return P((a - o).half(v), 0) < P((b - o).half(v), (a - o).cross(b - o));
	});
}
