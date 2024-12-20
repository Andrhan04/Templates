#pragma once
#include <math.h>
struct pt {
	double x, y;
	const double EPS = 1e-9;
	bool operator< (const pt& p) const {
		return x < p.x - EPS || fabs(x - p.x) < EPS && y < p.y - EPS;
	}
	pt(double x, double y) :x(x), y(y) {}
	pt operator = (const pt& other) {
		return other;
	}
};