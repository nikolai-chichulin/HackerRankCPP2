#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

typedef signed long long int li;

ofstream outf1, outf2, outf3;

void fillup(int k, int* a) {
    a[0] = 0;
    a[1] = k;
    for (int i = 2; i <= k; i++) {
        a[i] = 0;
    }
}

int getproduct(int k, const int* a) {
    int ret = 1;
    for (int i = 2; i <= k; i++) {
        ret *= int(pow(i, a[i]));
    }
    return ret;
}

int getsum(int k, const int* a) {
    int ret = 0;
    for (int i = 1; i <= k; i++) {
        ret += i * a[i];
    }
    return ret;
}

/// <summary>
/// Tries to balance the array so that the product is equal to the sum.
/// </summary>
/// <param name="k">Number of the terms.</param>
/// <param name="a">The array.</param>
/// <param name="i">Incremented term.</param>
/// <param name="j">Reduced term.</param>
bool balance(int k, int* a, int i, int j) {
    bool balanced = false;
    int p = getproduct(k, a);
    int s = getsum(k, a);
    int pprev = p;
    int sprev = s;
    while (true) {
        if (p > s) {
            a[i]--;
            a[j]++;
            p = pprev;
            s = sprev;
            break;
        }
        else if (p == s) {
            balanced = true;
            break;
        }
        a[i]++;
        a[j]--;
        pprev = p;
        sprev = s;
        p = getproduct(k, a);
        s = getsum(k, a);
    }
    if (balanced) {
        cout << "Balanced:" << endl;
    }
    else {
        cout << "Not balanced:" << endl;
    }
    cout << "a[" << i << "] = " << a[i] << endl;
    cout << "a[" << j << "] = " << a[j] << endl;
    cout << "P = " << p << "; S = " << s << endl;
    return balanced;
}

void solve() {

    //outf1.open("test1.out");
    //outf2.open("test2.out");
    //outf3.open("test3.out");

    auto start = std::chrono::high_resolution_clock::now();

    //
    const int k = 12000;
    int* a = new int[k + 1];
    fillup(k, a); // initial fill-up with 1-s

    int i = 2; // incremented
    int j = 1; // decremented
    int aiprev = a[i];
    int ajprev = a[j];
    while (!balance(k, a, i, j)) {
        if (a[j] == ajprev) { // 
            a[j]--;
            a[j - 1]++;
        }
        else {
            i++;
            j++;
        }
        aiprev = a[i];
        ajprev = a[j];
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    outf1 << "Execution time    = " << t << " s" << endl;

    //outf1.close();
    //outf2.close();
    //outf3.close();
}

int main() {

    solve();

    return 0;
}
