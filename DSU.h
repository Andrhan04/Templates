#pragma once
#include <vector>
class DSU {
public:
	DSU(int n) {
		p.resize(n);
		for (int i = 0; i < n; ++i) {
			p[i] = i;
		}
	}
	void Unite(int x, int y) {
		unite(x, y);
	}
	int Find(int x) {
		return find(x);
	}
private:
	std::vector<int> p;
	int find(int x) {
		if (p[x] == x) {
			return x;
		}
		return p[x] = find(p[x]);
	}
	void unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x != y) {
			if (rand() & 1)
				p[x] = y;
			else
				p[y] = x;
		}
	}
};