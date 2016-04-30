#include <cstdio>
#include <cstring>
#include <algorithm>

int const N = 200100;
double const PI = 3.14159265358979323846;

struct comp {
    double re, im;
    
    comp() : 
    	re(0), im(0) {}
    
    comp(int x) : 
    	re(x), im(0) {}
    
    comp(double a, double b) : 
    	re(a), im(b) {}
    
    comp operator+(comp const& a) const {
        return comp(re + a.re, im + a.im);
    }

    comp operator-(comp const& a) const {
        return comp(re - a.re, im - a.im);
    }

    comp& operator*=(comp const& a) {
        double newRe = re * a.re - im * a.im;
        im = re * a.im + im * a.re;
        re = newRe;
        return *this;
    }

    comp& operator/=(double a) {
    	re /= a;
    	im /= a;
        return *this;
    }
};

comp operator*(comp const& a, comp const& b) {
	return a *= b;
}

void FFT(comp* a, int n, bool const inv) {                                           
    for (int i = 1, j = 0; i < n; ++i) {                                                                                    
        int bit = n >> 1;                                                                                         
        while (j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if (i < j) {                                                                            
            std::swap(a[i], a[j]);                                                                                 
        }                                                                                                         
    }
    for (int len = 2; len <= n; len <<= 1) {                            
        double angle = 2 * PI / len;                                
        if (inv) {                                                  
            angle = -angle;                                     
        }                                                           
        comp const g(cos(angle), sin(angle));                
        for (int i = 0; i < n; i += len) {                          
            comp r = comp(1);                                   
            for (int j = 0; j < len / 2; ++j) {                 
                comp x = a[i + j];                          
                comp y = r * a[i + j + len / 2];            
                a[i + j] = x + y;                           
                a[i + j + len / 2] = x - y;                 
                r *= g;                                  
            }                                                                                                  
        }                                                                                                              
    }                                                                                                                                                         
    if (inv) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

int p1[N], p2[N], p3[N];

comp ta[N], tb[N];

void mul(int sz) {
    int n = 1;
    while (n < sz) {
        n <<= 1;
    }
    n <<= 1;
    for (int i = 0; i < sz; ++i) {
        ta[i] = comp(p1[i]);
    }
    for (int i = 0; i < sz; ++i) {
        tb[i] = comp(p2[i]);
    }
    for (int i = sz; i < n; ++i) {
    	ta[i] = 0;
    	tb[i] = 0;
    }
    FFT(ta, n, false);
    FFT(tb, n, false);
    for (int i = 0; i < n; ++i) {
        ta[i] *= tb[i];
    }
    FFT(ta, n, true);
	for (int i = 0; i < n; ++i) {
		p3[i] = (int) (ta[i].re + 0.5);
	}
}

int main() {

}