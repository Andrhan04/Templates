#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Graf_with_breadge {
private:
#define Graf vector<vector<int>>
	Graf g;
	vector<bool> used;
	vector<int> tin, fup;
	int timer;
	int n;
	void dfs(int v, int p = -1) {
		used[v] = true;
		tin[v] = fup[v] = timer++;
		for (auto u : g[v]) {
			if (u == p)  continue; // не смотрим предка
			if (used[u]) {
				fup[v] = min(fup[v], tin[u]);
			}
			else {
				dfs(u, v);
				fup[v] = min(fup[v], fup[u]);
				if (fup[u] > tin[v])
					IS_BRIDGE(v, u);
			}
		}
	}
public:
	vector<int> ans;
	void IS_BRIDGE(int a, int b) {
		cout << "BRIDGE" << a << ' ' << b << endl;
	}
	void find_bridges(Graf& g, vector<char>& used, vector<int>& tin, vector<int>& fup) {
		// Мостом называется такое РЕБРО, удаление которого делает граф несвязным(или, точнее, увеличивает число компонент связности).
		timer = 0;
		for (int i = 0; i < n; ++i)
			if (!used[i])
				dfs(i, -1);
	}
	Graf_with_breadge(Graf& my) {
		g = my;
		n = my.size();
		timer = 0;
		tin.resize(n);
		fup.resize(n);
		used.resize(n);
	}
};
