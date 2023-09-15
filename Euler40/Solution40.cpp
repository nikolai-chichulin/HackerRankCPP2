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

int main() {

    makesk();

    li i = 1234567l;
    li k = getk(i);

    return 0;
}
