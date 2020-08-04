uniform_int_distribution<int> dis(970, 1030);
const int gsize = dis(rng);
sort(all(queries), [&](const Query& a, const Query& b) {
	const int ga = a.l / gsize;
  const int gb = b.l / gsize;
  return (ga == gb) ? (ga & 1) ? a.r < b.r : a.r > b.r : a.l < b.l;
});