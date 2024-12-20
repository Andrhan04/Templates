#pragma once
#include <vector>
#include <algorithm>
using namespace std;

class Grekhem {
private:
	class Point {
	public:
		double x, y;
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
	bool is_left_rotate(Point a, Point b, Point c) {
		return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) < 0;
	}
	bool is_right_rotate(Point a, Point b, Point c) {
		return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) > 0;
	}
public:
	void convex_hull(vector<Point>& points) {
		if (points.size() == 1) return;
		sort(points.begin(), points.end());
		Point p1 = points[0], p2 = points.back();
		vector<Point> up, down;
		up.push_back(p1);
		down.push_back(p1);
		for (int i = 1; i < points.size(); ++i) {
			if (i == points.size() - 1 || is_left_rotate(p1, points[i], p2)) {
				while (up.size() >= 2 && !is_left_rotate(up[up.size() - 2], up[up.size() - 1], points[i]))
					up.pop_back();
				up.push_back(points[i]);
			}
			if (i == points.size() - 1 || is_right_rotate(p1, points[i], p2)) {
				while (down.size() >= 2 && !is_right_rotate(down[down.size() - 2], down[down.size() - 1], points[i]))
					down.pop_back();
				down.push_back(points[i]);
			}
		}
		points.clear();
		for (int i = 0; i < up.size(); ++i)
			points.push_back(up[i]);
		for (int i = down.size() - 2; i > 0; --i)
			points.push_back(down[i]);
	}
};