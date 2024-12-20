#pragma once
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
#include <set>
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