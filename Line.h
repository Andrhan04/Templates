#pragma once
#include <algorithm>
#include "Point.h"
using namespace std;
class Line
{
public:
	inline bool betw(double l, double r, double x) {
		return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
	}
	Line(double A, double B, double C) {
		a = A;
		b = B;
		c = C;
		norm();
	}
	Line(pt p, pt q) {
		a = p.y - q.y;
		b = q.x - p.x;
		c = -a * p.x - b * p.y;
		norm();
	}

	bool parallel(Line n) {
		return abs(det(a, b, n.a, n.b)) < EPS;
	}
	bool operator == (Line& other) {
		return abs(det(a, b, other.a, other.b)) < EPS
			&& abs(det(a, c, other.a, other.c)) < EPS
			&& abs(det(b, c, other.b, other.c)) < EPS;
	}
	bool intersect(Line& other, pt& res) {
		double zn = det(a, b, other.a, other.b);
		if (abs(zn) < EPS)
			return false;
		res.x = -det(c, b, other.c, other.b) / zn;
		res.y = -det(a, c, other.a, other.c) / zn;
		return true;
	}

	inline bool intersect_1d(double a, double b, double c, double d) {
		if (a > b)  swap(a, b);
		if (c > d)  swap(c, d);
		return max(a, c) <= min(b, d) + EPS;
	}
	bool intersect(pt& a, pt& b, pt& c, pt& d, pt& left, pt& right) {
		if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
			return false;
		Line m(a, b);
		Line n(c, d);
		double zn = det(m.a, m.b, n.a, n.b);
		if (abs(zn) < EPS) {
			if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
				return false;
			if (b < a)  swap(a, b);
			if (d < c)  swap(c, d);
			left = max(a, c);
			right = min(b, d);
			return true;
		}
		else {
			left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
			left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
			return betw(a.x, b.x, left.x)
				&& betw(a.y, b.y, left.y)
				&& betw(c.x, d.x, left.x)
				&& betw(c.y, d.y, left.y);
		}
	}

	double dist(pt p) const {
		return a * p.x + b * p.y + c;
	}
private:
	double a, b, c;
	const double EPS = 1e-9;
	double det(double a, double b, double c, double d) {
		return a * d - b * c;
	}
	void norm() {
		double z = sqrt(a * a + b * b);
		if (abs(z) > EPS)
			a /= z, b /= z, c /= z;
	}
};
