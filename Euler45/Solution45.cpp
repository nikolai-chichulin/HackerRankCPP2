#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

typedef long long int li;
const li dim = 1000000000000001;

int ncount = 0;
vector<li> res;

li p(li n) {
    return n * (3 * n - 1) / 2;
}

li t(li n) {
    return n * (n + 1) / 2;
}

li h(li n) {
    return n * (2 * n - 1);
}

/// <summary>
/// Test if a number n is equal to the polynom am^2 + bm + c
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <param name="c"></param>
/// <param name="n"></param>
/// <returns></returns>
li isapolynom(li a, li b, li c, li n) {
    li d = b * b - 4l * a * (c - n);
    li m = li((-b + sqrt(d)) / (2l * a));
    li res = a * m * m + b * m + c;
    if (res == n) {
        return m;
    }
    return -1l;
}

void solveBF(li a, li b, li upperbound) {
    if ((a == 3 && b == 5) || (a == 5 && b == 6)) {

        // Tn = n(n+1)/2
        // Pn = n(3n-1)/2
        // Hn = n(2n-1)

        li nmax = 25000000;
        for (li n = 0; n < nmax; n++) {
            li pn = p(n);
            if (pn < upperbound) {
                if (a == 3 && b == 5) { // Pn = Tm
                    li m = isapolynom(1l, 1l, 0, 2l * pn); // Pn = Tm?
                    if (m > 0) {
                        li tm = t(m);
                        if (tm < upperbound) {
                            ncount++;
                            res.push_back(pn);
                            cout << pn << " : " << n << " " << m << endl;
                        }
                    }
                }
                else { // Pn = Hm
                    li m = isapolynom(2l, -1l, 0, pn); // Pn = Hm?
                    if (m > 0) {
                        li hm = h(m);
                        if (hm < upperbound) {
                            ncount++;
                            res.push_back(pn);
                            cout << pn << " : " << n << " " << m << endl;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    li n = 200000000000000;
    li a = 3;
    li b = 5;

    solveBF(a, b, n);

    if (ncount > 0) {
        for (li r : res) {
            cout << r << endl;
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
}
