#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

int dp[10005] , max_depth[10005] = {0};

void diameter_of_tree(vector<vector<int>> &tree , int src) {
	if (tree[src].size() == 0) {
		dp[src] = 0; //max_depth[src] = 0; already
		return;
	}

	if (dp[src] != -1) {
		return;
	}
	for (auto x : tree[src]) {
		diameter_of_tree(tree , x);
	}

	if (tree[src].size() == 1) {
		max_depth[src] = max_depth[tree[src][0]] + 1;
		dp[src] = dp[tree[src][0]] + 1;
	}

	else {
		int maxi = INT_MIN , second_maxi = INT_MIN;
		for (auto x : tree[src]) {
			int y = maxi;
			maxi = max(maxi , max_depth[x]);
			second_maxi = max(second_maxi , min(y , max_depth[x]));
		}

		dp[src] = maxi + second_maxi + 2;
		max_depth[src] = maxi + 1;
	}
	return;
}

int main() {
	int n;
	cin >> n;
	vector<vector<int> > tree;
	tree.reserve(n + 1);
	for (int i = 0 ; i < n - 1 ; i++) {
		int u , v;
		cin >> u >> v;
		tree[u].push_back(v);
	}
	memset(dp , -1 , sizeof(dp));
	diameter_of_tree(tree , 1);
	int maxi = INT_MIN;
	for (int i = 1 ; i <= n ; i++) {
		maxi =  max(maxi , dp[i]);
	}
	cout << maxi << endl;
	return 0;

}
