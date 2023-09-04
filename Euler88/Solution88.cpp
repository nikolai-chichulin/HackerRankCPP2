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
const int dim = 300000;
int mask[dim] = {};
const int maxprime = 280000; // maximal prime number
bool isprime[maxprime] = {};
const int numofprimes = 50000; // number of primes
int primes[numofprimes] = {};

void getprimes() {
    for (int i = 2; i < maxprime; i++) {
        isprime[i] = true;
    }
    for (int i = 2; i < maxprime; i++) {
        if (isprime[i]) {
            int jst = i * i;
            for (int j = jst; j < maxprime; j += i) {
                isprime[j] = false;
            }
        }
    }
    int iprime = 0;
    for (int i = 0; i < maxprime; i++) {
        if (isprime[i]) {
            primes[iprime++] = i;
        }
    }
}

void solve(int k) {

}

int solve_sum(int k) {

    outf.open("test_sum.dat");

    auto start = std::chrono::high_resolution_clock::now();

    // make the mask
    solve(k);

    // calculate the sum
    int sum = 0;
    for (int ik = 2; ik < dim; ik++) {
        if (mask[ik] > 0 && mask[ik] <= k)
            sum += ik;
    }

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
