#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Graf_with_LCA {
private:
#define Graf vector<vector<int>>
	Graf up;
	vector<int> d;
	Graf g;
	void dfs(int u, int p) {
		int sz = up[u].size() - 1;
		up[u][0] = p;

		for (int i = 1; i <= sz; i++) {
			if (up[u][i - 1] != -1) {
				up[u][i] = up[up[u][i - 1]][i - 1];
			}
		}
		for (int neighbor : g[u]) {
			if (neighbor != p) {
				d[neighbor] = d[u] + 1;
				dfs(neighbor, u);
			}
		}
	}
public:
	int Get_LCA(int a, int b) {
		int sz = up[a].size() - 1;

		if (d[a] < d[b]) {
			swap(a, b);
		}

		for (int i = sz; i >= 0; i--) {
			if (d[a] - (1 << i) >= d[b]) {
				a = up[a][i];
			}
		}

		if (a == b) {
			return a;
		}

		for (int i = sz; i >= 0; i--) {
			if (up[a][i] != -1 && up[a][i] != up[b][i]) {
				a = up[a][i];
				b = up[b][i];
			}
		}

		return up[a][0];
	}

	void build_graf() {
		int n;
		cin >> n;

		Graf g(n);

		int buf, u;
		for (int i = 0; i < n; i++) {
			cin >> buf;
			for (int j = 0; j < buf; j++) {
				cin >> u;
				g[i].push_back(u);
				g[u].push_back(i);
			}
		}
		int s = ceil(log2(n)) + 1;
		up.assign(n, vector<int>(s, -1));
		d.assign(n, 0);
		dfs(0, -1);
	}
	Graf_with_LCA() {}
	Graf_with_LCA(Graf& my) {
		g = my;
	}
};