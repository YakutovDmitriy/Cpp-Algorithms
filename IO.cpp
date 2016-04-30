#include <cstdio>

namespace io {
int const BUF_SIZE = 40960;
int rpos, rlen;
char rbuf[BUF_SIZE];
int wpos;
char wbuf[BUF_SIZE];

int getch() {
	if (rpos >= rlen) {
		rpos = 0;
		rlen = fread(rbuf, 1, BUF_SIZE, stdin);
	}
	return rbuf[rpos++];
}

template<typename T>
T next() {
	int ch = getch();
	while (ch <= 32) ch = getch();
	bool sign = false;
	if (ch == '-') {
		sign = true;
		ch = getch();
	}
	T ret = 0;
	while (ch > 32) {
		ret = 10 * ret + ch - '0';
		ch = getch();
	}
	return sign ? -ret : ret;
}

auto const nextint = next<int>;
auto const nextlong = next<long long>;

void flush() {
	if (wpos > 0) {
		fwrite(wbuf, 1, wpos, stdout);
		wpos = 0;
	}
}

struct Autoflusher {
	~Autoflusher() {
		io::flush();
	}
} autoflusher;

void putch(char x) {
	if (wpos == BUF_SIZE) flush();
	wbuf[wpos++] = x;
}

void putstr(char const* s) {
	while (*s) putch(*s++);
	putch('\n');
}

template<typename T>
void putnum(T x) {
	static char numbuf[50];
	int sz = 0;
	if (x < 0) {
		putch('-');
		x = -x;
	}
	do {
		numbuf[sz++] = x % 10 + '0';
		x /= 10;
	} while (x != 0);
	while (sz-- > 0) putch(numbuf[sz]);
}
};

int main() {
	long long x = io::nextlong();
	io::putnum(x);
	io::putch('\n');
	io::putstr("abac");
}