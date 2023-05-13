#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

int nop = 0;

bool ismaskequal(int* mask1, int* mask2) {
    for (int i = 0; i < 10; i++) {
        if (mask1[i] != mask2[i]) {
            return false;
        }
    }
    return true;
}

int tointeger(const string& s) {
    int ret = 0;
    int tens = 1;
    for (int i = 0; i < s.size(); i++) {
        ret += tens * int((s[s.size() - i - 1] - '0'));
        tens *= 10;
    }
    return ret;
}

string tostring(int n) {
    string ret;
    int order = int(log10(double(n)));
    int tens = int(pow(10, order));
    while (tens > 0) {
        int i = int(n / tens);
        ret.push_back(i + '0');
        n -= i * tens;
        tens /= 10;
    }
    return ret;
}

void getmask(int n, int* mask) {
    int order = int(log10(double(n)));
    int tens = int(pow(10, order));
    while (tens > 0) {
        int i = int(n / tens);
        mask[i]++;
        n -= i * tens;
        tens /= 10;
        nop += 2;
    }
}

void test2() {

    int n1 = 125874;
    int n2 = 125874 * 2;

    int mask1[] = { 0,0,0,0,0,0,0,0,0,0 };
    getmask(n1, mask1);
    int mask2[] = { 0,0,0,0,0,0,0,0,0,0 };
    getmask(n2, mask2);

    if (ismaskequal(mask1, mask2)) {
        cout << "Masks are equal!" << endl;
    }
    else {
        cout << "Masks are not equal!" << endl;
    }
}

bool equaldigits(int n1, int n2) {
    int order1 = int(log10(double(n1)));
    int order2 = int(log10(double(n2)));
    if (order1 != order2) { // counts of digits are different
        return false;
    }
    int mask1[] = { 0,0,0,0,0,0,0,0,0,0 };
    getmask(n1, mask1);
    int mask2[] = { 0,0,0,0,0,0,0,0,0,0 };
    getmask(n2, mask2);
    return ismaskequal(mask1, mask2);
}

void test() {
    bool ret = true;
    for (int i = 0; i <= 1000000; i++) {
        string str = tostring(i);
        int i2 = tointeger(str);
        if (i != i2) {
            ret = false;
            break;
        }
    }
    if (ret) {
        cout << "Passed" << endl;
    }
    else {
        cout << "Failed" << endl;
    }
}

void solve(int nmax, int kmax) {
    for (int n1 = 1; n1 <= nmax; n1++) {
        bool found = true;
        for (int k = 2; k <= kmax; k++) {
            int n2 = n1 * k;
            if (!equaldigits(n1, n2)) {
                found = false;
                break;
            }
        }
        if (found) {
            cout << n1;
            for (int k = 2; k <= kmax; k++) {
                cout << " " << n1 * k;
            }
            cout << endl;
        }
    }
}

void solvePE(int nmax, int kmax) {
    for (int n1 = 1000; n1 <= nmax; n1++) {
        bool found = true;
        for (int k = 3; k <= kmax; k++) {
            int n2 = n1 * k;
            if (equaldigits(n1 * 2, n2)) {
                // cout << n1 << " ~ " << n2 << " : " << k << endl;
            }
            else {
                found = false;
                break;
            }
        }
        if (found) {
            cout << n1;
            for (int k = 2; k <= kmax; k++) {
                cout << " ~ " << n1 * k;
            }
            cout << endl;
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    //
    // test();
    // test2();
    solve(2000000, 6);
    cout << "N operations: " << nop << endl;
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
