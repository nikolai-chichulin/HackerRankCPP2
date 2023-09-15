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

ofstream outf;

const li dim = 17l;
li sk[dim] = {};
li decimals[] = { 1l,10l,100l,1000l,10000l,100000l,1000000l,10000000l,100000000l,1000000000l,10000000000l,100000000000l,1000000000000l,10000000000000l,100000000000000l,1000000000000000l,10000000000000000l,100000000000000000l,1000000000000000000l };

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

void solve(li i) {
    li k = getk(i); // find the range
    li is = k == 0 ? i : i - sk[k - 1]; // 1-based position inside the k-th range
    li iss = is % (k + 1) == 0 ? is / (k + 1) : is / (k + 1) + 1; // 1-based number of the k-digit number in the range
    li number = decimals[k] + iss - 1;
    cout << "i = " << i << " k = " << k << " is = " << is << " iss = " << iss << " number = " << number << endl;
}

int main() {

    makesk();

    li i = 193l; // 1-based position of the digit started from the left
    solve(i);

    return 0;
}
