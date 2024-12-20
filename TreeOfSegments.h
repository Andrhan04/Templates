#pragma once
#include <vector>
#include <algorithm>
using namespace std;
class TreeOfSegments { // Дерево Отрезков
private:
#define int long long
	int n = 0;
	const int neitral = 0;
	struct Vertex {
		int sum;
		int cnt_min, min;
		int cnt_max, max;
		Vertex() : sum(0), min(1e9 + 7), cnt_min(0), cnt_max(0), max(-1) {}   // Дефолтные значения
		Vertex(int x) : sum(x), min(x), cnt_min(1), cnt_max(1), max(x) {} // Старовые значения
	};
	vector<Vertex> Tree;

	Vertex combination(Vertex a, Vertex b) {
		Vertex res = Vertex();
		res.sum = a.sum + b.sum; // сумма
		if (a.min == b.min) { // если одинаковый минимум
			res.min = a.min;
			res.cnt_min = a.cnt_min + b.cnt_min;
		}
		else {
			if (a.min < b.min) { // у а меньше минимум
				res.min = a.min;
				res.cnt_min = a.cnt_min;
			}
			else { // у b меньше минимум
				res.min = b.min;
				res.cnt_min = b.cnt_min;
			}
		}
		if (a.max == b.max) { // если одинаковый max
			res.max = a.max;
			res.cnt_max = a.cnt_max + b.cnt_max;
		}
		else {
			if (a.max > b.max) { // у а max больше
				res.max = a.max;
				res.cnt_max = a.cnt_max;
			}
			else { // у b max больше
				res.max = b.max;
				res.cnt_max = b.cnt_max;
			}
		}
		return res;
	}

	void update(int pos, int value, int index, int l, int r) {
		if (l == r) {
			Tree[index] = Vertex(value);
			return;
		}
		int m = (l + r) / 2;
		if (pos <= m) {
			update(pos, value, 2 * index + 1, l, m);
		}
		else {
			update(pos, value, 2 * index + 2, m + 1, r);
		}
		Tree[index] = combination(Tree[2 * index + 1], Tree[2 * index + 2]);
	}

	Vertex get(int l, int r, int tl, int tr, int pos) {
		if (l > r) return Vertex();
		if (l == tl && r == tr) return Tree[pos];
		int tm = (tl + tr) / 2;
		return combination(get(l, min(tm, r), tl, tm, 2 * pos + 1), get(max(l, tm + 1), r, tm + 1, tr, 2 * pos + 2));
	}

public:
	void Build(vector<int>& array) {
		n = (int)(array.size());
		Tree.resize(4 * n + 7);
		for (int i = 0; i < n; i++) {
			update(0, n, i, array[i], 0);
		}
	}

	void Update(int pos, int value) {
		update(pos, value, 0, 0, n);
	}

	vector<int> Get(int l, int r) {
		vector<int> v(5);
		auto buf = get(l, r, 0, n, 0);
		v[0] = buf.sum;
		v[1] = buf.min;
		v[2] = buf.cnt_min;
		v[3] = buf.max;
		v[4] = buf.cnt_max;
	}
};