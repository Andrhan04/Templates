#pragma once
#include <vector>
using namespace std;
class TreeFenvic { // Дерево Фенвика
private:
	vector<vector<int>> t;
	int n = 0, m = 0;
	void init(int nn, int mm) {
		n = nn; m = mm;
		t.resize(n, vector<int>(mm, 0));
	}
	int sum(int x, int y) {
		int result = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
				result += t[i][j];
		return result;
	}
	void inc(int x, int y, int delta) {
		for (int i = x; i < n; i = (i | (i + 1)))
			for (int j = y; j < m; j = (j | (j + 1)))
				t[i][j] += delta;
	}
public:
	void build(int nn, int mm) {
		init(nn, mm);
	}
	void add(int x, int y) {
		inc(x, y, 1);
	}
	void erase(int x, int y) {
		inc(x, y, -1);
	}
	int get(int x1, int y1, int x2, int y2) {
		return sum(x2, y2) - sum(x1, y1) - sum(x1, y2) - sum(x2, y1);
	}
};