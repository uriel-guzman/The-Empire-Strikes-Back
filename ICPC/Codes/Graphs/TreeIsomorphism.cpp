#include <bits/stdc++.h>
#define endl '\n'
#define MOD(n,k) ( ( ((n) % (k)) + (k) ) % (k))
#define forn(i,n) for (int i = 0; i < n; i++)
#define rep(i, a, b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i <= b; i++)
#define pb(x) push_back(x)
#define fi first
#define se second
#define all(v) v.begin(), v.end()
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

const int MX = 300005, CN = 3;
const int mod[] = {
	1000000021,
	1000000009,
	998244353
};

int n;
ll b[CN];
vi adj[MX], h[MX], cero(CN);
set<vi> st;

void dfs (int u, int p) {
	h[u] = vi(CN, 1);

	for (int v : adj[u])
		if (v != p) {
			dfs(v, u);	
			forn (i, CN) (h[u][i] *= (h[v][i] * b[i] + 1) % mod[i]) %= mod[i];
		}
}

void re_root (int u, int p, vi w) {
	vi a = h[u];
	forn (i, CN) (a[i] *= (w[i] * b[i] + 1) % mod[i]) %= mod[i];
	st.insert(a);

	vi lis;
	vector<vi> pre;
	for (int v : adj[u])
		if (v != p) {
			lis.pb(v);
			pre.pb(h[v]);
		}

	vector<vi> suf = pre;
	reverse(all(suf));

	forn (k, pre.size()) 
		forn (i, CN) {
			pre[k][i] = (pre[k][i] * b[i] + 1) % mod[i];
			if (k) (pre[k][i] *= pre[k - 1][i]) %= mod[i];

			suf[k][i] = (suf[k][i] * b[i] + 1) % mod[i];
			if (k) (suf[k][i] *= suf[k - 1][i]) %= mod[i];
		}

	reverse(all(suf));

	forn (k, lis.size()) {
		vi x(CN, 1);

		forn (i, CN) {
			(x[i] *= (w[i] * b[i] + 1) % mod[i]) %= mod[i];
			if (k) (x[i] *= pre[k - 1][i]) %= mod[i];
			if (k + 1 < lis.size()) (x[i] *= suf[k + 1][i]) %= mod[i];
		}

		re_root(lis[k], u, x);
	}
}

int main () {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

	forn (i, CN) {
		uniform_int_distribution<> dis(0, mod[i] - 1);
		b[i] = dis(rng);
	}

	cin >> n;
	forn (i, n - 1) {
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	dfs(1, 1);
	re_root(1, 1, cero);

	cout << st.size() << endl;

	return 0;
}
