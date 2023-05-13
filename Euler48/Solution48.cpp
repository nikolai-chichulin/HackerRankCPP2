#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

const int dim = 2000001;
const int dim_primes = 150000;
typedef long long int li;
li s[dim]; // the terms: S = s1 + s2 + s3 + ... + sN, where s2 = 2^2, s30 = 30^30, sN = N^N
li primes[dim_primes]; // primes <= 2 000 000
bool isprime[dim];

void getprimes() {
    for (li i = 2; i < dim; i++) {
        isprime[i] = true;
    }
    cout << " ---//--- " << endl;
    for (li i = 2; i < dim; i++) {
        if (isprime[i]) {
            li jst = i * i;
            for (li j = jst; j < dim; j += i) {
                isprime[j] = false;
            }
        }
        //cout << " --- " << endl;
    }
}


int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    getprimes();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
