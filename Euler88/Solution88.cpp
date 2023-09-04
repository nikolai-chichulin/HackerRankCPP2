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
        if (isprime[i]) {
            divisors[i][0] = i;
            continue;
        }
        int v = i;
        int id = 0;
        for (int prime : primes) {
            if (prime > v) {
                break;
            }
            while (v % prime == 0) {
                v /= prime;
                divisors[i][id++] = prime;
            }
        }
        if (id > id_max) {
            id_max = id;
            cout << "id_max = " << id_max << " i = " << i << endl;
        }
        //cout << i << " done" << endl;
    }
    cout << "getdivisors done!" << endl;
}

void solve(int k) {

    getprimes();
    getdivisors();

}

int solve_sum(int k) {

    outf.open("test_prime_factorization.dat");

    auto start = std::chrono::high_resolution_clock::now();

    // make the mask
    solve(k);

    // calculate the sum
    int sum = 0;
    //for (int ik = 2; ik < dim; ik++) {
    //    if (mask[ik] > 0 && mask[ik] <= k)
    //        sum += ik;
    //}

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Answer         = " << sum << endl;
    cout << "Execution time = " << t << " s" << endl;
    outf << "Answer         = " << sum << endl;
    outf << "Execution time = " << t << " s" << endl;

    outf.close();
    return sum;
}

int main() {

    int k = 200000;
    int res = solve_sum(k);

    return 0;
}
