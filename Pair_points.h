#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Pair_points {
private:
	class Point {
	public:
		double x, y;
		int id;
		bool operator > (Point& other) {
			return (x > other.x || x == other.x && y > other.y);
		}
		bool operator < (Point& other) {
			return (x < other.x || x == other.x && y < other.y);
		}
		bool operator == (Point& other) {
			return (x == other.x && y == other.y);
		}
		bool operator != (Point& other) {
			return !(x == other.x && y == other.y);
		}
	};
	vector<Point> a;
	double mindist;
	int ansa, ansb;
	void upd_ans(const Point& a, const Point& b) {
		double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
		if (dist < mindist)
			mindist = dist, ansa = a.id, ansb = b.id;
	}
	void rec(int l, int r) {
		if (r - l <= 3) {
			for (int i = l; i <= r; ++i)
				for (int j = i + 1; j <= r; ++j)
					upd_ans(a[i], a[j]);
			sort(a.begin() + l, a.begin() + r + 1, [](Point a, Point b) {return a.y < b.y; });
			return;
		}

		int m = (l + r) >> 1;
		int midx = a[m].x;
		rec(l, m), rec(m + 1, r);
		vector<Point> t(a.size());
		merge(a.begin() + l, a.begin() + m + 1, a.begin() + m + 1, a.begin() + r + 1, t.begin(), &[](Point a, Point b) {return a.y < b.y; });
		copy(t.begin(), t.begin() + r - l + 1, a.begin() + l);

		int tsz = 0;
		for (int i = l; i <= r; ++i)
			if (abs(a[i].x - midx) < mindist) {
				for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
					upd_ans(a[i], t[j]);
				t[tsz++] = a[i];
			}
	}
public:
	void GetAns(int n, vector<pair<double, double>>& arr) {
		a.resize(n);
		int index = 0;
		for (auto& i : a) {
			i.x = arr[index].first;
			i.y = arr[index].second;
			i.id = index;
			index++;
		}
		sort(a.begin(), a.end());
		mindist = 1E20;
		rec(0, n - 1);
		for (auto i : a) {
			cout << i.x << i.y << i.id << endl;
		}
	}
};
