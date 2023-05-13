#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

const int dim = 1000000;
typedef long long int li;
vector<li> pnumbers;

void makenumbers() {
    pnumbers.push_back(0);
    for (li i = 1; i <= dim; i++) {
        li p = i * (3 * i - 1) / 2;
        pnumbers.push_back(p);
    }
}

bool ispentagonal(li p) {
    int i = dim / 2;
    auto ret = find(begin(pnumbers), end(pnumbers), p);
    return ret != end(pnumbers);
}

li ispentagonalBinarySearch(li p) {
    li il = 1;
    li ir = dim;
    while (true)
    {
        li i = (il + ir) / 2;
        if (p == pnumbers[i]) {
            return i;
        }
        else {
            if (ir == il + 1) {
                if (p == pnumbers[il]) {
                    return il;
                }
                if (p == pnumbers[ir]) {
                    return ir;
                }
                break;
            }
            if (p > pnumbers[i]) {
                il = i;
            }
            else {
                ir = i;
            }
        }
    }
    return -1;
}

void solve(li nmax, li k) {
    for (li n = k + 1; n < nmax; n++) {
        li diff = pnumbers[n] - pnumbers[n - k];
        li sum = pnumbers[n] + pnumbers[n - k];
        auto resdiff = ispentagonalBinarySearch(diff);
        auto ressum = ispentagonalBinarySearch(sum);
        if (resdiff != -1 || ressum != -1) {
            //cout << endl;
            //cout << "Solution found for k = " << k << endl;
            //cout << "P[" << n << "] (" << pnumbers[n] << ") - P[" << n - k << "] (" << pnumbers[n - k] << ") = " << diff << " (P[" << resdiff << "])" << endl;
            //cout << "P[" << n << "] (" << pnumbers[n] << ") + P[" << n - k << "] (" << pnumbers[n - k] << ") = " << sum << " (P[" << ressum << "])" << endl;
            cout << pnumbers[n] << endl;
        }
    }
}

void solve(li nmax) {
    for (li k = 1; k < 10000; k++) {
        cout << k << " ";
        solve(nmax, k);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    makenumbers();
    solve(10, 2);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
