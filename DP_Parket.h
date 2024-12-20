#pragma once
#include <vector>
using namespace std;

class Parket {
private:
#define int long long
	int n = 0, m = 0;
	vector <vector<int>> levels;
	void calc(int level = 0, int bit = 0, int mask = 0, int next_mask = 0) {
		if (level == n) {
			return;
		}
		if (bit >= m) {
			levels[level + 1][next_mask] += levels[level][mask];
		}
		else {
			int my_mask = 1 << bit;
			if (mask & my_mask) {
				calc(level, bit + 1, mask, next_mask);
			}
			else {
				calc(level, bit + 1, mask, next_mask | my_mask);
				if (bit + 1 < m && !(mask & my_mask) && !(mask & (my_mask << 1))) {
					calc(level, bit + 2, mask, next_mask);
				}
			}
		}
	}
public:
	int Get_ans(int nn, int mm) {
		n = nn; m = mm;
		levels.resize(n + 1, vector<int>(1 << m));
		levels[0][0] = 1;
		for (int x = 0; x < n; x++) {
			for (int mask = 0; mask < (1 << m); mask++) {
				calc(x, 0, mask, 0);
			}
		}
		return levels[n][0];
	}
};