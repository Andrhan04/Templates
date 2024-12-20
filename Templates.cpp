#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#include <list>
#include <stack>
#include <string>
#include <numeric>
#include <algorithm>
using namespace std;

class SQRTdec {
private:
	struct Query {
		int l, r, id;
	};
	vector<int> arr;
	int K = sqrt(arr.size());
	vector<int> cnt;
	int a = 1, b = 0; // создаём пустой рабочий отрезок 
	bool isLess(Query a, Query b) {
		if (a.l / K != b.l / K)return a.l < b.l;
		return a.r < b.r;
	}
	map<int, int>cntmp;
	set<pair<int, int>>cur;
	void func(vector<Query>q) {
		vector<int>res(q.size());
		for (int i = 0; i < arr.size(); i++) {
			cntmp[arr[i]]++;
		}
		for (int i = 0; i < arr.size(); i++) {
			cnt[arr[i]] = cntmp[arr[i]];//элементы массива не превышают его длину  
			cur.insert({ cnt[arr[i]], arr[i] });
		}
		sort(q.begin(), q.end(), isLess);
		for (int i = 0; i < q.size(); i++) {
			while (a > q[i].l) {
				add(a - 1);//left 
				a -= 1;
			}
			while (b < q[i].r) {
				add(b + 1);//right 
				b += 1;
			}
			while (a < q[i].l) {
				del(a);//left 
				a += 1;
			}
			while (b > q[i].r) {
				del(b);//right 
				b -= 1;
			}
			res[q[i].id] = answer();// получаем ответ на [a...b] 
		}
	}
public:
	void add(int index) {
		int value = arr[index];
		if (cnt[value] > 0)
			cur.erase({ cnt[value], value });
		cnt[arr[index]] += 1;
		cur.insert({ cnt[value], value });
	}
	void del(int index) {
		int value = arr[index];
		cur.erase({ cnt[value], value });
		cnt[arr[index]] -= 1;
		if (cnt[value] > 0)
			cur.insert({ cnt[value], value });
	}
	int answer() {
		auto i = --cur.end();
		return i->second; // находим максимальную пару в множестве 
	}
	SQRTdec(vector<int>& v) {
		arr = v;
		int K = sqrt(v.size());
		cnt.resize(arr.size() + 1);
	}
};

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
			cout << array[i] << ' ';
		}
		cout << endl;
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

class TreeFenvic { // Дерево Фенвика
private:
	vector <vector <int> > t;
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
	vector<int> p;
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

class KMP {
private:
#define all(v) (v).begin() , (v).end()
	int n = 0;
	vector<int> pi;
	void prefix_function(string s) {
		n = (int)s.length();
		pi.resize(n);
		for (int i = 1; i < n; ++i) {
			int j = pi[i - 1];
			while (j > 0 && s[i] != s[j])
				j = pi[j - 1];
			if (s[i] == s[j])  ++j;
			pi[i] = j;
		}
	}
public:
	void build(string s) {
		n = s.size();
		pi.resize(n);
	}

	int CountSub(string str) {
		int n = str.length();
		int cnt = 0;
		prefix_function(str);
		for (int i = 0; i < n; i++) {
			cnt += (i + 1 - pi[i]);
		}

		return cnt;
	}
};

class Graf_with_LCA {
private:
#define Graf vector<vector<int>>
	Graf up;
	vector<int> d;
	Graf g;
	void dfs(int u, int p) {
		int sz = up[u].size() - 1;
		up[u][0] = p;

		for (int i = 1; i <= sz; i++) {
			if (up[u][i - 1] != -1) {
				up[u][i] = up[up[u][i - 1]][i - 1];
			}
		}
		for (int neighbor : g[u]) {
			if (neighbor != p) {
				d[neighbor] = d[u] + 1;
				dfs(neighbor, u);
			}
		}
	}
public:
	int Get_LCA(int a, int b) {
		int sz = up[a].size() - 1;

		if (d[a] < d[b]) {
			swap(a, b);
		}

		for (int i = sz; i >= 0; i--) {
			if (d[a] - (1 << i) >= d[b]) {
				a = up[a][i];
			}
		}

		if (a == b) {
			return a;
		}

		for (int i = sz; i >= 0; i--) {
			if (up[a][i] != -1 && up[a][i] != up[b][i]) {
				a = up[a][i];
				b = up[b][i];
			}
		}

		return up[a][0];
	}

	void build_graf() {
		int n;
		cin >> n;

		Graf g(n);

		int buf, u;
		for (int i = 0; i < n; i++) {
			cin >> buf;
			for (int j = 0; j < buf; j++) {
				cin >> u;
				g[i].push_back(u);
				g[u].push_back(i);
			}
		}
		int s = ceil(log2(n)) + 1;
		up.assign(n, vector<int>(s, -1));
		d.assign(n, 0);
		dfs(0, -1);
	}
	Graf_with_LCA() {}
	Graf_with_LCA(Graf& my) {
		g = my;
	}
};

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

struct pt {
	double x, y;
	const double EPS = 1e-9;
	bool operator< (const pt& p) const {
		return x < p.x - EPS || abs(x - p.x) < EPS && y < p.y - EPS;
	}
	pt(double x, double y) :x(x), y(y) {}
	pt operator = (const pt& other) {
		return other;
	}
};

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

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Graf_with_CUTPOINT {
private:
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

class Graf_with_breadge {
private:
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

int main()
{
	std::cout << "Hello World!\n";
}