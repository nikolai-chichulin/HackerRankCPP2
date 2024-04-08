#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long int li;

const int nprimes = 100000;
const int maxnum = 500000;

li primes[nprimes];
bool isprime[maxnum];

int mask[maxnum] = {};

void getprimes() {
    for (li i = 2; i < maxnum; i++) {
        isprime[i] = true;
    }
    for (li i = 2; i < maxnum; i++) {
        if (isprime[i]) {
            li jst = i * i;
            for (li j = jst; j < maxnum; j += i) {
                isprime[j] = false;
            }
        }
    }
    int iprime = 0;
    for (int i = 0; i < maxnum; i++) {
        if (isprime[i]) {
            primes[iprime++] = i;
        }
    }
}

void make_mask() {
    int res_max = 0;
    for (int k = 1; k < maxnum; k++) {
        int res1 = 2 * k * k;
        if (res1 >= maxnum) {
            break;
        }
        for (int prime : primes) {
            int res = res1 + prime;
            if (res >= maxnum) {
                break;
            }
            if (res > res_max) {
                res_max = res;
            }
            mask[res]++;
        }
    }
}

void solveHR() {
    int T = 0;
    cin >> T;

    for (int it = 0; it < T; it++) {
        int N = 0;
        cin >> N;
        cout << mask[N] << endl;
    }
}

void solvePE() {
    for (int i = 0; i < maxnum; i++) {
        if (i % 2 == 1 && !isprime[i] && mask[i] == 0) {
            cout << i << endl;
        }
    }
}

int main() {

    getprimes();
    make_mask();

    // solveHR();
    solvePE();

    return 0;
}
