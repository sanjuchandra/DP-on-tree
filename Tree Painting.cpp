#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <cstring>


using namespace std;
#define ll long long

ll n;
ll dp[200005] = {0};
ll size[200005] = {0};
vector<vector<ll>> adjList(200005);
ll ans = 0;

void dfs1(ll node , ll par) {
	for (auto x : adjList[node]) {
		if (x != par) {
			dfs1(x , node);
			dp[node] += dp[x];
			size[node] += size[x];
		}
	}
	size[node] += 1;
	dp[node] += size[node];
}


void dfs2(ll node , ll par , ll upper_dp) {
	ll val = dp[node] + upper_dp + n - size[node];
	ans = max(ans , val);
	for (auto x : adjList[node]) {
		if (x != par) {
			ll contri = dp[x] + size[x]; //contribution of this child
			dfs2(x , node , val - contri);
		}
	}
}



int main() {
	cin >> n;
	for (ll i = 0 ; i < n - 1 ; i++) {
		ll x , y;
		cin >> x >> y;
		adjList[x].push_back(y);
		adjList[y].push_back(x);
	}

	dfs1(1 , 0);
	dfs2(1 , 0 , 0);
	cout << ans << endl;


	return 0;
}
