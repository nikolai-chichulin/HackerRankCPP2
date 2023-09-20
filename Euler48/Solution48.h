#ifndef SOLUTION48_H
#define SOLUTION48_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

ofstream outf;

const int dim = 2000001;
const int dim_primes = 150000;
typedef unsigned long long int ul;
const ul tol = 10000000000l;
const ul maxlisqr = ul(sqrt(LLONG_MAX));

ul s[dim]; // the terms: S = s1 + s2 + s3 + ... + sN, where s2 = 2^2, s30 = 30^30, sN = N^N
ul primes[dim_primes]; // primes <= 2 000 000
bool isprime[dim];

const ul edge = 4200000000l;
const ul edge_2 = 2 * edge;
const ul edge_05 = edge / 2;

ul memo[100000000] = {};
bool marked[dim] = {};

int ncalls1 = 0;
int ncalls2 = 0;
int ncalls3 = 0;

void getprimes() {
    for (ul i = 2; i < dim; i++) {
        isprime[i] = true;
    }
    // cout << " ---//--- " << endl;
    for (ul i = 2; i < dim; i++) {
        if (isprime[i]) {
            ul jst = i * i;
            for (ul j = jst; j < dim; j += i) {
                isprime[j] = false;
            }
        }
        //cout << " --- " << endl;
    }
}

bool is_small(ul n) {
    return n <= edge;
}

bool product_is_small(ul n1, ul n2) {
    return (n1 < edge) && (n2 < edge);
}

ul safe_mod_multiplication_rec(ul a, ul b, ul m) {
    ul ret = 0;
    if (product_is_small(a, b)) {
        ret = (a * b) % m;
        //outf << "Debug safe_mod_multiplication small: a = " << a << " b = " << b << " ret = " << ret << endl;
    }
    else {
        ul mx = a > b ? a : b; // maximum
        ul mn = mx == a ? b : a; // minimum
        if (mx % 2l == 0) {
            ul mx_2 = mx / 2l;
            ret = (2 * safe_mod_multiplication_rec(mx_2, mn, m)) % m;
        }
        else {
            ul mx_2 = (mx - 1l) / 2l;
            ret = (2 * safe_mod_multiplication_rec(mx_2, mn, m)) % m;
            ret = (ret + mn) % m;
        }
        //outf << "Debug safe_mod_multiplication big: a = " << a << " b = " << b << " ret = " << ret << endl;
    }
    return ret;
}

ul safe_mod_square(ul a) {
    if (a <= edge) {
        ncalls1++;
        return (a * a) % 10000000000l;
    }
    ncalls2++;

    ul ret = 0;
    ul ar = a % 1000000000l;
    ul r1 = (((a / 1000000000l) * ar) % 10) * 1000000000l;
    ul r3 = (ar * ar) % 10000000000l;
    return (r1 + r1 + r3) % 10000000000l;
}

ul safe_mod_multiplication(ul a, ul b) {
    if (product_is_small(a, b)) {
        ncalls1++;
        return (a * b) % 10000000000l;
    }
    ncalls2++;

    ul ret = 0;
    ul ar = a % 1000000000l;
    ul br = b % 1000000000l;
    ul r1 = (((a / 1000000000l) * br) % 10) * 1000000000l;
    ul r2 = (((b / 1000000000l) * ar) % 10) * 1000000000l;
    ul r3 = (ar * br) % 10000000000l;
    return (r1 + r2 + r3) % 10000000000l;
}

ul mod_power(ul base, ul exp, ul m) {
    ul ret = 1;
    for (int i = 0; i < exp; i++) {
        ret *= base;
        ret %= m;
        if (ret == 0) {
            break;
        }
    }
    return ret;
}

ul mod_binpow(ul a, ul b) {
    ul ret = 1;
    while (b > 0) {
        if (b & 1)
            ret = safe_mod_multiplication(ret, a); // (res * a) % m;
        a = safe_mod_square(a);
        b >>= 1;
    }
    return ret;
}

#endif // !SOLUTION48_H
