#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

typedef long long ls; // long signed
typedef vector<ls> vl; // vector of ls

void print_vector(ostream& ostr, vl& v) {
    for (ls i : v) {
        ostr << i << " ";
    }
    ostr << endl;
}

/// <summary>
/// Converts an integer to the vector form with a given base.
/// </summary>
/// <param name="n">The integer.</param>
/// <param name="base">The base.</param>
/// <returns></returns>
vl convert_to_vector(ls n, ls base) {
    vl ret;
    ls m = n;
    while (m != 0) {
        ls rem = m % base;
        ret.push_back(rem);
        m /= base;
    }
    return ret;
}

ls convert_to_number(const vl& v, ls base) {
    ls ret = 0;
    ls bases = 1;
    for (ls i : v) {
        ret += bases * i;
        bases *= base;
    }
    return ret;
}

/// <summary>
/// Converts an integer as a vector to the vector with another base.
/// </summary>
/// <param name="n">The integer.</param>
/// <param name="base">The base.</param>
/// <returns></returns>
//vl rebase_as_vector(const vl& n, ls base) {
//    vl ret;
//    ls m = n;
//    while (m != 0) {
//        ls rem = m % base;
//        ret.push_back(rem);
//        m /= base;
//    }
//    return ret;
//}

void looping(int nd, int level, int nmax, int* v) {
    int last_level = nd == 2 ? 1 : nd == 3 || nd == 4 ? 2 : 3;
    if (level == last_level) {
        return;
    }
    for (int digit = level == 0 ? 1 : 0; digit < 10; digit++) {
        v[level] = digit;
        v[nd - level - 1] = v[level];
        looping(nd, level + 1, nmax, v);
    }
}

void solve_impl(ls nmax) {

    int nd = 2;
    while (true) {

        // nd=2 => loop through 1 digit


    }

}

void solve(ls nmax) {
    auto start = std::chrono::high_resolution_clock::now();

    for (ls n = 1; n < nmax; n++) {
        vl res = convert_to_vector(n, 2);
        ls nn = convert_to_number(res, 2);
        if (nn != n) {
            cout << "Alarm at n = " << n << "; nn = " << nn << endl;
        }
        //if (n % 100000 == 0) {
        //    cout << n << endl;
        //    print_vector(cout, res);
        //    cout << nn << endl;
        //    cout << "-----" << endl;
        //}
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time = " << t << " s" << endl;
}

int main() {

    solve(1000000);

    return 0;
}
