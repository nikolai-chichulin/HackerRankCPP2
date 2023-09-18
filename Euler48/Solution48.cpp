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
const ul edge_05 = edge / 2;;

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
    if (n1 < edge && n2 < edge) {
        return true;
    }
    else if (n1 < edge_2 && n2 < edge_05) {
        return true;
    }
    else if (n1 < edge_05 && n2 < edge_2) {
        return true;
    }
    return false;
}

ul safe_mod_multiplication(ul a, ul b, ul m) {
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
            ret = (2 * safe_mod_multiplication(mx_2, mn, m)) % m;
        }
        else {
            ul mx_2 = (mx - 1l) / 2l;
            ret = (2 * safe_mod_multiplication(mx_2, mn, m)) % m;
            ret = (ret + mn) % m;
        }
        //outf << "Debug safe_mod_multiplication big: a = " << a << " b = " << b << " ret = " << ret << endl;
    }
    return ret;
}

void safe_mod_multiplication_test() {
    bool passed = true;

    ul n1 = 4836715601l;
    ul n2 = 2569995622l;
    ul res_exp = 9429098822l;
    ul res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 3415897173l;
    n2 = 5114489489l;
    res_exp = 6813314597l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 654654654656l;
    n2 = 54654354768l;
    res_exp = 1546999808l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 4294967296l;
    n2 = 2147483648l;
    res_exp = 6854775808l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 8642381783621l;
    n2 = 45111235899977l;
    res_exp = 2412876717l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 1l;
    n2 = 1l;
    res_exp = 1l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 1l;
    n2 = 2l;
    res_exp = 2l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 2l;
    n2 = 2l;
    res_exp = 4l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 11l;
    n2 = 22l;
    res_exp = 242l;
    res = safe_mod_multiplication(n1, n2, tol);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    if (passed) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed!" << endl;
    }
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

ul mod_binpow(ul a, ul b, ul m) {
    //cout << "Debug: a = " << a << " b = " << b;
    ul ret = 1;
    while (b > 0) {
        if (b & 1)
            ret = safe_mod_multiplication(ret, a, m); // (res * a) % m;
        a = safe_mod_multiplication(a, a, m); // (a * a) % m;
        b >>= 1;
    }
    //cout << " ret = " << ret << endl;
    return ret;
}

void test() {
    ul N = 2000000l;
    ul s1 = 0;
    ul s2 = 0;
    for (ul a = 1l; a <= N; a++) {
        //ul c1 = mod_power(a, a, tol);
        ul c2 = mod_binpow(a, a, tol);
        //if (c1 != c2) {
        //    cout << " Failed for a = " << a << "!!!" << endl;
        //}
        //s1 += c1;
        //s1 %= tol;
        s2 = (s2 + c2) % tol;

        //if (a % 100000 == 0)
        //    cout << a << " done" << endl;
    }
    cout << "Sum1 = " << s1 << " Sum2 = " << s2 << endl;
}

void test_one() {
    ul a = 1999999l;
    ul b = 1999999l;
    ul c1 = mod_power(a, b, tol);
    cout << "c1 = " << c1 << endl;
    ul c2 = mod_binpow(a, b, tol);
    cout << "c2 = " << c2 << endl;

    if (c1 != c2) {
        cout << " Failed!!!" << endl;
    }
    else {
        cout << " Passed!!!" << endl;
    }
}

int main() {

    outf.open("Euler48.out");

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    //solveBF(10000);
    test();
    //test_one();
    //safe_mod_multiplication_test();

    outf.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
