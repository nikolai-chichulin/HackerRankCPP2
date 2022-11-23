#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>
#include <string>

using namespace std;

typedef long long li;
typedef size_t sz;

const int lim = 100000000;
bool isprime[lim];
int s[lim];

bool isaprime(int n) {

    if (n == 2 || n == 3) {
        return true;
    }

    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (int i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

int tonumber(const string& s) {
    int ret = 0;
    int tens = 1;
    for (int i = 0; i < s.size(); i++) {
        ret += tens * (s[s.size() - i - 1] - '0');
        tens *= 10;
    }
    return ret;
}

void solve(int n) {

    // Get primes
    for (sz i = 2; i < lim; i++) {
        isprime[i] = true;
    }
    for (sz i = 2; i < lim; i++) {
        if (isprime[i]) {
            sz jst = i * i;
            for (sz j = jst; j < lim; j += i) {
                isprime[j] = false;
            }
        }
    }

    // Solve
    sz maxlen = 0;
    for (sz ind = 2; ind < 100; ind++) {
        if (isprime[ind]) {
            sz len = 0;
            int maxval = 0;
            sz lentmp = 0;
            int stmp = 0;
            int ilast = -1;
            for (int i = ind; i < 6000000; i++) {
                if (isprime[i]) {
                    stmp += i;
                    lentmp++;
                    if (stmp > n) {
                        //cout << i << endl;
                        break;
                    }
                    if (isprime[stmp]) { // sum is a prime
                        if (lentmp > len) {
                            len = lentmp;
                            maxval = stmp;
                            ilast = i;
                        }
                    }
                }
            }
            if (len > maxlen) {
                maxlen = len;
                cout << "ind = " << ind << ": maxlen = " << len << " maxval = " << maxval << " ilast = " << ilast << endl;
            }
        }
    }
}

void test() {

    int n = 0;
    for (int i = 0; i <= 500000; i++) {
        bool ispr = isaprime(1000000000 + i);
        if (ispr)
            n++;
    }
    cout << n << endl;
}

int main() {

    int n = 80000000;

    auto start = std::chrono::high_resolution_clock::now();
    //
    test();
    //solve(n);
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
