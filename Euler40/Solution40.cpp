#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

typedef long long li; // long integer

const li dim = 17l;
li sk[dim] = {};
li powers_of_ten[] = { 1l,10l,100l,1000l,10000l,100000l,1000000l,10000000l,
100000000l,1000000000l,10000000000l,100000000000l,1000000000000l,10000000000000l,
100000000000000l,1000000000000000l,10000000000000000l,100000000000000000l,1000000000000000000l };

/// <summary>
/// Construct the array Sk = 9 + 2*90 + 3*900 + ... + k*10^k
/// </summary>
void makesk() {
    li s = 0;
    li n = 1l;
    li dec = 9l;
    for (li i = 0; i < dim; i++) {
        li ds = n * dec;
        s += ds;
        sk[i] = s;
        dec *= 10l;
        n++;
    }
}

li getk(li i) {
    li k = 0l;
    while (i > sk[k]) {
        k++;
        if (k == dim) {
            return -1l;
        }
    }
    return k;
}

/// <summary>
/// Returns a digit which is placed at the given position in the given number.
/// </summary>
/// <param name="n">The number.</param>
/// <param name="order">Decimal order of the number.</param>
/// <param name="position">1-based position started from the begining (highest order).</param>
/// <returns></returns>
li getdigit(li n, li order, li position) {


    //li m = n;
    //while (m != 0) {
    //    li rem = m % 10;
    //    ret.push_back(rem);
    //    m /= 10;
    //}
    //return ret;


    li left = n % powers_of_ten[order + 2 - position];
    li right = powers_of_ten[order + 1 - position];
    li ret = left / right;
    return ret;
}

li solve(li i) {
    li k = getk(i); // find the range
    li is = k == 0 ? i : i - sk[k - 1]; // 1-based position inside the k-th range
    li iss = is % (k + 1) == 0 ? is / (k + 1) : is / (k + 1) + 1; // 1-based number of the k-digit number in the range
    li number = powers_of_ten[k] + iss - 1; // the number containing the given digit i
    li isss = is - (k + 1) * (iss - 1); // 1-based position of the i inside the number
    li digit = getdigit(number, k, isss);
    cout << "i = " << i << " k = " << k << " is = " << is << " iss = " << iss << " number = " << number << " isss = " << isss << " digit = " << digit << endl;
    return digit;
}

int main() {

    makesk();

    li res = 1;
    li i = 1111101l; // 1-based position of the digit started from the left
    li d = solve(i);
    res *= d;
    i = 2111102l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;
    i = 3111103l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;
    i = 4111104l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;
    i = 5111105l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;
    i = 6111106l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;
    i = 7111107l; // 1-based position of the digit started from the left
    d = solve(i);
    res *= d;

    cout << "Answer = " << res << endl;

    return 0;
}
