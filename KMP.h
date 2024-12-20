#pragma once
#include <vector>
#include <string>
using namespace std;

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