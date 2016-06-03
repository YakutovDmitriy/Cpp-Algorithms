#include <bits/stdc++.h>

typedef long long ll;

int const MOD = 1000000007;
ll const MOD2 = (ll) MOD * MOD;
int const MAXN = 4;

template<int size, typename A, typename B, typename C>
void add(A a, B b, C where) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			where[i][j] = a[i][j] + b[i][j];
			if (where[i][j] >= MOD) {
				where[i][j] -= MOD;
			}
		}
	}
}

template<int size, typename A, typename B, typename C>
void sub(A a, B b, C where) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			where[i][j] = a[i][j] + MOD - b[i][j];
			if (where[i][j] >= MOD) {
				where[i][j] -= MOD;
			}
		}
	}
}

template<int size, typename T, typename S>
void copy(T what, S where) {
	for (int i = 0; i < size; ++i) {
		std::copy(what[i], what[i] + size, where[i]);
	}
}

template<int size>
void stupidMul(int a[size][size], int b[size][size], int where[size][size]) {
	static int c[size][size];
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {

			ll coef = 0;
			
			for (int k = 0; k < size; ++k) {
				coef += (ll) a[i][k] * b[k][j];
				if (coef >= MOD2) coef -= MOD2;
			}
			
			c[i][j] = coef % MOD;
		}
	}
	
	copy<size>(c, where);
}

template<int size, int half = ((size + 1) >> 1)>
void mul(int n, int a[size][size], int b[size][size], int where[size][size]) {

	static int aa[2][2][half][half];
	static int bb[2][2][half][half];
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			aa[i >= half][j >= half][i & (half - 1)][j & (half - 1)] = a[i][j];
			bb[i >= half][j >= half][i & (half - 1)][j & (half - 1)] = b[i][j];
		}
	}

	static int p[7][half][half];
	static int x[7][half][half];
	static int y[7][half][half];
	
	add<half>(aa[0][0], aa[1][1], x[0]);
	add<half>(bb[0][0], bb[1][1], y[0]);
	
	add<half>(aa[1][0], aa[1][1], x[1]);
	copy<half>(bb[0][0], y[1]);
	
	copy<half>(aa[0][0], x[2]);
	sub<half>(bb[0][1], bb[1][1], y[2]);
	
	copy<half>(aa[1][1], x[3]);
	sub<half>(bb[1][0], bb[0][0], y[3]);
	
	add<half>(aa[0][0], aa[0][1], x[4]);
	copy<half>(bb[1][1], y[4]);
	
	sub<half>(aa[1][0], aa[0][0], x[5]);
	add<half>(bb[0][0], bb[0][1], y[5]);
	
	sub<half>(aa[0][1], aa[1][1], x[6]);
	add<half>(bb[1][0], bb[1][1], y[6]);


	for (int i = 0; i < 7; ++i) {
		if (n - 1 > MAXN) {
			mul<half>(n - 1, x[i], y[i], p[i]);
		} else {
			stupidMul<half>(x[i], y[i], p[i]);
		}
	}
	
	static int cc[2][2][half][half];
	
	add<half>(p[0], p[3], cc[0][0]);
	sub<half>(cc[0][0], p[4], cc[0][0]);
	add<half>(cc[0][0], p[6], cc[0][0]);
	
	add<half>(p[2], p[4], cc[0][1]);
	
	add<half>(p[1], p[3], cc[1][0]);
	
	sub<half>(p[0], p[1], cc[1][1]);
	add<half>(cc[1][1], p[2], cc[1][1]);
	add<half>(cc[1][1], p[5], cc[1][1]);
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			where[i][j] = cc[i >= half][j >= half][i & (half - 1)][j & (half - 1)];
		}
	}

}

int rnd(int x, int y) {
	return rand() % (y - x + 1);
}


int const n = 6;
int const size = 1 << n;

int a[size][size], b[size][size], c[size][size], d[size][size];

int main() {
	srand(1510);
	
	for (int it = 0; it < 10100; ++it) {
		
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				a[i][j] = rnd(0, 111);
				b[i][j] = rnd(0, 222);
			}
		}
		
		mul(n, a, b, c);
		stupidMul(a, b, d);
	
		bool eq = true;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				eq &= c[i][j] == d[i][j];
			}
		}
		
		if (!eq) {
			fprintf(stderr, "oops %d\n", it);
			break;
		} else {
			fprintf(stderr, "ok %d\n", it);
		}
		
	}
	
} 