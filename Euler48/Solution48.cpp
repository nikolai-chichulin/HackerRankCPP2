#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

const int dim = 2000001;
const int dim_primes = 150000;
typedef unsigned long long int li;
const li tol = 10000000000l;
const li maxlisqr = li(sqrt(LLONG_MAX));

li s[dim]; // the terms: S = s1 + s2 + s3 + ... + sN, where s2 = 2^2, s30 = 30^30, sN = N^N
li primes[dim_primes]; // primes <= 2 000 000
bool isprime[dim];

void getprimes() {
    for (li i = 2; i < dim; i++) {
        isprime[i] = true;
    }
    // cout << " ---//--- " << endl;
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

li power(li base, li exp) {
    li ret = 1;
    for (int i = 0; i < exp; i++) {
        ret *= base;
        ret %= tol;
        if (ret == 0) {
            break;
        }
    }
    return ret;
}

li binpow(li a, li b, li m) {
    a %= m;
    li res = 1;
    while (b > 0) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

li binpowrec(li a, li b, li m) {
    if (b == 0) {
        return 1l;
    }
    li c = binpowrec(a, b / 2, m);
    if (b % 2 == 0) {
        if (c > maxlisqr) {
            cout << " danger c for a = " << a << " ";
        }
        c *= c;
        return c % m;
    }
    c *= c;
    return a * c % m;
}

void solveBF(li n) {
    li ret = 0;
    for (li i = 1; i < n + 1; i++) {
        li t = power(i, i);
        ret += t;
        ret %= tol;
        if (i % 100 == 0)
            cout << "i = " << i << " : " << ret << endl;
    }
    cout << "n = " << n << " : " << ret << endl;
}

void test() {
    for (li a = 2l; a < 100l; a++) {
        li c1 = power(a, a);
        li c2 = binpow(a, a, tol);
        li c3 = binpowrec(a, a, tol);
        cout << " a = " << a << " : res1 = " << c1 << " res2 = " << c2 << " res3 = " << c3 << endl;
    }
}

int findOdd(int arr[], int n)
{
    int res = 0, i;
    for (i = 0; i < n; i++)
        res ^= arr[i];
    return res;
}

// Driver Method
int solve1()
{
    int arr[] = { 12, 12, 14, 90, 14, 14, 14 };
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The odd occurring element is %d ",
        findOdd(arr, n));
    return 0;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    //solveBF(10000);
    test();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
