#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

ofstream outf;

const int pmax = numeric_limits<int>::max();
const int dim = 200001;
int mask[dim] = {};
const int maxprime = 280000; // maximal prime number exclusive
bool isprime[maxprime] = {};
const int numofprimes = 25000; // number of primes, upper limit
int primes[numofprimes] = {};
int numofprimesact = 0;

int divisors[dim][20] = {};
int sum[dim] = {};

int kfromn[dim][100] = {};
int nminfromk[2 * dim] = {};

void getprimes() {
    for (int i = 2; i < maxprime; i++) {
        isprime[i] = true;
    }
    for (int i = 2; i < maxprime; i++) {
        if (isprime[i]) {
            int jst = i * i;
            if (jst < maxprime) {
                for (int j = jst; j < maxprime; j += i) {
                    isprime[j] = false;
                }
            }
            else {
                break;
            }
        }
    }
    for (int i = 0; i < maxprime; i++) {
        if (isprime[i]) {
            primes[numofprimesact++] = i;
        }
    }
}

void getdivisors() {
    int id_max = 0;
    for (int i = 1; i < dim; i++) {
        // divisors[i] is a list of i-th divisors
        int id = 0; // divisor index
        if (isprime[i]) {
            divisors[i][0] = i;
            sum[i] = i;
            id = 1;
        }
        else {
            int v = i;
            for (int prime : primes) {
                if (prime > v) {
                    break;
                }
                while (v % prime == 0) {
                    v /= prime;
                    divisors[i][id++] = prime;
                    sum[i] += prime;
                }
            }
            if (id > id_max) {
                id_max = id;
                cout << "id_max = " << id_max << " i = " << i << endl;
            }
        }
        //cout << i << " done" << endl;

        // calulate k for this factorization
        int k = i - sum[i] + id;
        if (mask[i] == 0) {
            mask[i] = k;
        }
    }
    cout << "getdivisors done!" << endl;
}

int getk(int p, int s, int nd) {
    return p - s + nd;
}

int getmink(int n) {

    if (mask[n] != 0) {
        return mask[n];
    }
    if (isprime[n]) {
        return 1;
    }

    int kmin = numeric_limits<int>::max();
    for (int d = 2; d < n / 2 + 1; d++) {
        if (n % d == 0) {
            int nn = n / d;
            int k = getmink(nn) + (d - 1) * (nn - 1);
            if (k == 10) {
                cout << n << endl;
            }
            kfromn[n][++kfromn[n][0]] = k;
            if (nminfromk[k] == 0 || (nminfromk[k] > 0 && n < nminfromk[k])) {
                nminfromk[k] = n;
            }
            if (k < kmin) {
                kmin = k;
            }
        }
    }
    //cout << n << " done: " << kmin << endl;
    if (mask[n] == 0) {
        mask[n] = kmin;
    }
    return kmin;
}

void solve(int k) {

    getprimes();
    //int n = 8;
    //int res = getk(n);
    //cout << " k[n=" << n << "] = " << res << endl;

    for (int n = 16; n >= 16; n--) {
        int res = getmink(n);
        //cout << " k[n=" << n << "] = " << res << endl;
    }

    //getdivisors();

}

int solve_sum(int k) {

    outf.open("test_prime_factorization.dat");

    auto start = std::chrono::high_resolution_clock::now();

    // make the mask
    solve(k);

    // calculate the sum
    int res = 0;
    //for (int ik = 2; ik < dim; ik++) {
    //    if (mask[ik] > 0 && mask[ik] <= k)
    //        sum += ik;
    //}

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Answer         = " << res << endl;
    cout << "Execution time = " << t << " s" << endl;
    outf << "Answer         = " << res << endl;
    outf << "Execution time = " << t << " s" << endl;

    outf.close();
    return res;
}

int main() {

    int k = 200000;
    int res = solve_sum(k);

    return 0;
}
