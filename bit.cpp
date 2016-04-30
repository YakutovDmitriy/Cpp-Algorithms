#include <vector>

struct BIT {
	int n;
	std::vector<long long> a;
	
	BIT() {}
	
	BIT(int n) :
		n(n) {
		a.resize(n + 1);
	}
	
	void add(int pos, int value) {
		for (int i = pos + 1; i <= n; i += i & -i) {
			a[i] += value;
		}
	}
	
	long long get_pref(int to) {
		long long ret = 0;
		for (int i = to; i > 0; i -= i & -i) {
			ret += a[i];
		}
		return ret;
	}
	
	long long get_sum(int from, int to) {
		return get_pref(to) - get_pref(from);
	}
};

int main() {

}