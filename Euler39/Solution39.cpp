#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

typedef long long li; // long integer

ofstream outf;

const int dim = 2000001;
bool isprime[dim];

li ntriples[5000001] = {};

void getprimes() {
    for (li i = 2; i < dim; i++) {
        isprime[i] = true;
    }
    for (li i = 2; i < dim; i++) {
        if (isprime[i]) {
            li jst = i * i;
            for (li j = jst; j < dim; j += i) {
                isprime[j] = false;
            }
        }
    }
}

void print_array(ostream& ostr, const int* v, int k) {
    for (int i = 0; i < k; i++) {
        ostr << v[i] << " ";
    }
    ostr << endl;
}

li isqrt(li i) {
    li ret = -1;
    li tmp = li(sqrt(i));
    li tmp_2 = tmp * tmp;
    if (tmp_2 == i) {
        ret = tmp;
    }
    return ret;
}

void solve_bf(li pmax) {
    int n = 0;
    int nb = 0;
    for (li a = 2; a < pmax / 2; a++) {
        li a_2 = a * a;
        //if (n % 10 == 0)
        //    cout << a << endl;
        for (li b = a; b < (pmax - a); b++) {
            if (!isprime[a])
                continue;
            li b_2 = b * b;
            li c_2 = a_2 + b_2;
            li maybe_c = isqrt(c_2);
            li p = a + b + maybe_c;
            if (maybe_c != -1 && p <= pmax) {
                n++;
                bool tmp1 = a % 3 == 0 && b % 4 == 0 && maybe_c % 5 == 0;
                bool tmp2 = a / 3 == b / 4;
                if (tmp1 && tmp2) {
                    nb++;
                    outf << n << ": " << a << " " << b << " " << maybe_c << " : P = " << p << " basic!" << endl;
                }
                else {
                    outf << n << ": " << a << " " << b << " " << maybe_c << " : P = " << p << endl;
                    cout << n << ": " << a << " " << b << " " << maybe_c << " : P = " << p << endl;
                }
            }
        }
    }
    outf << "nb=" << nb << endl;
}

li solve_ab(li pmax) {
    int n = 0;
    li amax = li(sqrt(pmax)) + 1;
    for (li a = 3; a < amax; a += 2) {
        li a_2 = a * a;
        for (li b = 1; b < a; b += 2) {
            li b_2 = b * b;
            li x = a * b;
            li y = (a_2 - b_2) / 2;
            li z = (a_2 + b_2) / 2;
            li p = x + y + z;
            if (p <= pmax) {
                // p is the perimeter of the primitive triple, we need all the multiplications up to pmax
                li ntriplesp = pmax / p;
                n++;
                //outf << n << ": a = " << a << " b = " << b << " x = " << x << " y = " << y << " z = " << z << " P = " << p << " N = " << ntriplesp << endl;
                for (li it = 1; it <= ntriplesp; it++) {
                    ntriples[p * it]++;
                }
            }
        }
    }

    li ipmax = 0;
    li ntriples_max = 0;
    for (li ip = 0; ip <= pmax; ip++) {
        if (ntriples[ip] > ntriples_max) {
            ntriples_max = ntriples[ip];
            ipmax = ip;
        }
    }
    return ipmax;
}

void solve() {
    outf.open("euler39.out");
    auto start = std::chrono::high_resolution_clock::now();

    //getprimes();
    cout << solve_ab(5000000) << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time = " << t << " s" << endl;
    outf.close();
}

int main() {
    solve();
    return 0;
}
