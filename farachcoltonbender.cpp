#include <bits/stdc++.h>

#if (_WIN32 || __WIN32__)
#  define LLD "%I64d"
#else
#  define LLD "%lld"
#endif

using std::istream; using std::ostream; using std::fixed; using std::greater;
using std::tuple; using std::tie; using std::make_pair; using std::multiset;
using std::nth_element; using std::min_element; using std::max_element;
using std::vector; using std::set; using std::map; using std::string;
using std::fill; using std::copy; using std::sort; using std::unique;
using std::unordered_set; using std::unordered_map; using std::pair;
using std::next_permutation; using std::reverse; using std::rotate;
using std::cin; using std::cout; using std::cerr; using std::endl;
using std::lower_bound; using std::upper_bound; using std::deque;
using std::min; using std::max; using std::swap; using std::abs;
using std::priority_queue; using std::queue; using std::bitset;
using std::make_tuple;

typedef long long ll;
typedef long double ld;

int const INF = (int) 1e9;
ll const INFL = (ll) 1e18;
ld const PI = 3.1415926535897932384626433832795028;



struct SparseTableRMQ {

    vector<int> a;
    vector<int> logs;
    vector<vector<int>> t;
    
    SparseTableRMQ() {}

    template<typename RAI>
    SparseTableRMQ(RAI A, RAI B) : a(A, B) {
        int sz = 1;
        while ((1 << sz) <= (int)a.size()) {
            sz++;
        }
        t = vector<vector<int>>(sz, vector<int>(a.size()));
        for (int i = 0; i < (int)a.size(); ++i) {
        	t[0][i] = i;
        }
        for (int i = 1; i < sz; i++) {
            int len = 1 << i;
            for (int j = 0; j + len <= (int)a.size(); j++) {
                int x = t[i - 1][j];
                int y = t[i - 1][j + (len >> 1)];
                t[i][j] = a[x] <= a[y] ? x : y;
            }
        }
        logs = vector<int>(a.size() + 1);
        for (int i = 2; i < (int)logs.size(); i++) {
            logs[i] = 1 + logs[i >> 1];
        }
    }

    int getMinPos(int from, int to) const {
        int i = logs[to - from];
        int x = t[i][from];
        int y = t[i][to - (1 << i)];
        return a[x] <= a[y] ? x : y;
    }

};


struct FCB1 {
	
    static const int MINIMAL_BLOCK_LENGTH = 5;

    vector<int> a;
    int blockLength;
    vector<vector<vector<int>>> blockDp;
    vector<int> typeOfBlock;
    SparseTableRMQ rmqOnBlocks;
    
    FCB1() {}

    template<typename RAI>
    FCB1(RAI A, RAI B) {
    	vector<int> arr(A, B);
        {
            int lg = 0;
            while ((1 << lg) < (int)arr.size()) {
                lg++;
            }
            blockLength = max(MINIMAL_BLOCK_LENGTH, lg / 2 + 1);
        }
        int blockCount;
        {
            blockCount = (arr.size() + blockLength - 1) / blockLength + 1;
            a = vector<int>(blockCount * blockLength);
            std::copy(arr.begin(), arr.end(), a.begin());
            for (int i = arr.size(); i < (int)a.size(); i++) {
                a[i] = a[i - 1] + 1;
            }
        }
        {
            int masksCount = 1 << (blockLength - 1);
            blockDp = vector<vector<vector<int>>>(masksCount);
            for (int mask = 0; mask < masksCount; mask++) {
                vector<int> cur(blockLength);
                for (int i = 1; i < blockLength; i++) {
                    if (((mask >> (i - 1)) & 1) == 1) {
                        cur[i] = cur[i - 1] + 1;
                    } else {
                        cur[i] = cur[i - 1] - 1;
                    }
                }
                blockDp[mask].resize(blockLength);
                for (int i = 0; i < blockLength; i++) {
                	blockDp[mask][i].resize(blockLength + 1);
                    int min = i;
                    for (int j = i + 1; j <= blockLength; j++) {
                        if (cur[j - 1] < cur[min]) {
                            min = j - 1;
                        }
                        blockDp[mask][i][j] = min;
                    }
                }
            }
        }
        {
            typeOfBlock = vector<int>(blockCount);
            for (int i = 0; i < blockCount; i++) {
                int start = i * blockLength;
                int end = start + blockLength;
                int mask = 0;
                for (int j = end - 1; j > start; j--) {
                    mask <<= 1;
                    mask |= a[j] > a[j - 1] ? 1 : 0;
                }
                typeOfBlock[i] = mask;
            }
        }
        {
        	vector<int> compressed(blockCount);
            for (int i = 0; i < blockCount; i++) {
                int mask = typeOfBlock[i];
                int index = i * blockLength + blockDp[mask][0][blockLength];
                compressed[i] = a[index];
            }
            rmqOnBlocks = SparseTableRMQ(compressed.begin(), compressed.end());
        }
    }

    int getMinPos(int from, int to) const {

        int fromBlock = from / blockLength;
        int fromMask = typeOfBlock[fromBlock];
        int fromStart = fromBlock * blockLength;
        int fromPos = from - fromStart;

        int toBlock = to / blockLength;
        int toMask = typeOfBlock[toBlock];
        int toStart = toBlock * blockLength;
        int toPos = to - toStart;

        if (fromBlock == toBlock) {
            return fromStart + blockDp[fromMask][fromPos][toPos];
        }

        int fromMin = fromStart + blockDp[fromMask][fromPos][blockLength];
        int toMin = toStart + blockDp[toMask][0][toPos];

        if (fromBlock == toBlock - 1) {
            return (toPos == 0 || a[fromMin] <= a[toMin]) ? fromMin : toMin;
        }

        int betweenBlock = rmqOnBlocks.getMinPos(fromBlock + 1, toBlock);
        int betweenStart = betweenBlock * blockLength;
        int betweenMask = typeOfBlock[betweenBlock];
        int betweenMin = betweenStart + blockDp[betweenMask][0][blockLength];

        int answer = fromMin;
        if (a[betweenMin] < a[answer]) {
            answer = betweenMin;
        }
        if (toPos > 0 && a[toMin] < a[answer]) {
            answer = toMin;
        }
        return answer;
    }

};


struct RMQLCATree {

    SparseTableRMQ rmq;
    vector<int> verticeOnPos;
	vector<int> firstPosition;
	
	RMQLCATree() {}
    
    RMQLCATree(vector<vector<int>> const& adjacents, int root) {
        int n = adjacents.size();
        verticeOnPos = vector<int>(n + n + 1);
        int curPos = 0;
        vector<int> depth(n);
        firstPosition = vector<int>(n);
        {
        	vector<int> vs(n + n + 1);
        	vector<int> ancs(n + n + 1);
            int sz = 0;
            vs[sz] = root;
            ancs[sz++] = root;
            while (sz > 0) {
                int v = vs[--sz];
                int anc = ancs[sz];
                if (anc >= 0) {
                    firstPosition[v] = curPos;
                    verticeOnPos[curPos++] = v;
                    for (int to : adjacents[v]) {
                        if (to != anc && to >= 0) {
                            depth[to] = depth[v] + 1;
                            vs[sz] = v;
                            ancs[sz++] = -1;
                            vs[sz] = to;
                            ancs[sz++] = v;
                        }
                    }
                } else {
                    verticeOnPos[curPos++] = v;
                }
            }
        }
        vector<int> toRmq(curPos);
        for (int i = 0; i < curPos; i++) {
            toRmq[i] = depth[verticeOnPos[i]];
        }
        rmq = SparseTableRMQ(toRmq.begin(), toRmq.end());
    }

    int getLCA(int a, int b) {
        int x = firstPosition[a];
        int y = firstPosition[b];
        if (x > y) {
            int temp = x;
            x = y;
            y = temp;
        }
        y++;
        return verticeOnPos[rmq.getMinPos(x, y)];
    }

};

struct FarachColtonBenderRMQ {

    RMQLCATree tree;
    
    FarachColtonBenderRMQ() {}

    template<typename RAI>
    FarachColtonBenderRMQ(RAI A, RAI B) {
    	vector<int> arr(A, B);
        int n = arr.size();
        vector<int> left(n, -1);
        vector<int> right(n, -1);
        vector<int> anc(n, -1);
        for (int i = 1; i < n; i++) {
            int cur = i - 1;
            while (anc[cur] >= 0 && arr[cur] > arr[i]) {
                cur = anc[cur];
            }
            if (arr[cur] > arr[i]) {
                anc[cur] = i;
                left[i] = cur;
            } else {
                left[i] = right[cur];
                if (left[i] >= 0) {
                    anc[left[i]] = i;
                }
                right[cur] = i;
                anc[i] = cur;
            }
        }
        vector<vector<int>> adjacents(n);
        int root = -1;
        for (int i = 0; i < n; i++) {
        	adjacents[i].resize(2);
            adjacents[i][0] = left[i];
            adjacents[i][1] = right[i];
            if (anc[i] < 0) {
                root = i;
            }
        }
        tree = RMQLCATree(adjacents, root);
    }

    int getMinPos(int from, int to) {
        return tree.getLCA(from, to - 1);
    }
};

int rnd(int x, int y) {
	static auto gen = std::bind(std::uniform_int_distribution<int>(), std::mt19937());
	return gen() % (y - x + 1) + x;
}

ll timer() {
	return (ld) clock() / CLOCKS_PER_SEC * 1000;
}

int const N = 5000000;
int const ITERS = 100000000;

void solve() {
	int n = N;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		a[i] = rnd(0, INF);
	}
	
	int built1 = timer();
	FarachColtonBenderRMQ rmq1(a.begin(), a.end());
	built1 = timer() - built1;
	
	int built2 = timer();
	SparseTableRMQ rmq2(a.begin(), a.end());
	built2 = timer() - built2;
	
	cerr << "built in " << timer() << endl;
	
	int sum1 = 0;
	int sum2 = 0;
	
	for (int it = 0; it < ITERS; ++it) {
	
		int from = rnd(0, n - 1);
		int to = rnd(from + 1, n);
		
		int start = timer();
		int p1 = rmq1.getMinPos(from, to);
		sum1 += timer() - start;
		
		start = timer();
		int p2 = rmq2.getMinPos(from, to);
		sum2 += timer() - start;
		
		assert(p1 == p2);
	
	}
	
	ld avg1 = (ld) sum1 / ITERS;
	ld avg2 = (ld) sum2 / ITERS;
	
	cerr << "FCB: built in " << built1 << " ms and for query " << (double) avg1 << " ms" << endl;
	cerr << "SpT: built in " << built2 << " ms and for query " << (double) avg2 << " ms" << endl;
}



int main() {

	cout.precision(15);
	cout << fixed;
	cerr.precision(6);
	cerr << fixed;
	
	srand(1510);

	solve();

#ifdef LOCAL
	cerr << "time: " << timer() << " ms" << endl;
#endif
}