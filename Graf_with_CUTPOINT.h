#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Graf_with_CUTPOINT {
private:
#define Graf vector<vector<int>>
	Graf g;
	int n;
	vector<int> tin;
	vector<int> fup;
	vector<bool> used;
	int timer;
	void dfs(int v, int p = -1) {
		used[v] = true;
		tin[v] = fup[v] = timer++;
		int children = 0;
		for (auto u : g[v]) {
			if (u == p)  continue;
			if (used[u])
				fup[v] = min(fup[v], tin[u]);
			else {
				dfs(u, v);
				fup[v] = min(fup[v], fup[u]);
				if (fup[u] >= tin[v] && p != -1)
					IS_CUTPOINT(v);
				++children;
			}
		}
		if (p == -1 && children > 1)
			IS_CUTPOINT(v);
	}
public:
	vector<int> ans;
	void IS_CUTPOINT(int a) {
		cout << "CUTPOINT " << a << endl;
		ans.push_back(a);
	}
	void Find() {
		timer = 0;
		dfs(0, -1);
	}
	Graf_with_CUTPOINT(Graf& my) {
		g = my;
		n = my.size();
		timer = 0;
		tin.resize(n);
		fup.resize(n);
		used.resize(n);
	}
};