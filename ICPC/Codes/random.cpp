uint32_t rng(uint32_t l = 0, uint32_t r = numeric_limits<uint32_t>::max()) {
  static mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
  return uniform_int_distribution<uint32_t>(l, r)(gen);
}
