#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class K, class V = null_type>
using ordered_tree = tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
// less_equal<K> for multiset, multimap (?
#define qrank order_of_key
#define qkth find_by_order