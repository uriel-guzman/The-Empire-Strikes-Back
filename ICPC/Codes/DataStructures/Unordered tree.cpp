#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct CustomHash {
  const uint64_t C = uint64_t(2e18 * 3) + 71;
  const int R = rng();
  uint64_t operator ()(uint64_t x) const {
    return __builtin_bswap64((x ^ R) * C); }
};

template <class K, class V = null_type>
using UnorderedTree = gp_hash_table<K, V, CustomHash>;