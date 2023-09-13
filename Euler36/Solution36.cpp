#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

typedef vector<int> vl; // vector of int

ofstream outf;

void print_array(ostream& ostr, const int* v, int k) {
    for (int i = 0; i < k; i++) {
        ostr << v[i] << " ";
    }
    ostr << endl;
}

/// <summary>
/// Converts an integer to the vector form with a given base.
/// </summary>
/// <param name="n">The integer.</param>
/// <param name="base">The base.</param>
/// <returns></returns>
vl convert_to_vector(int n, int base) {
    vl ret;
    int m = n;
    while (m != 0) {
        int rem = m % base;
        ret.push_back(rem);
        m /= base;
    }
    return ret;
}

int convert_to_array(int n, int base, int* v) {
    int m = n;
    int i = 0;
    while (m != 0) {
        int rem = m % base;
        v[i] = rem;
        m /= base;
        i++;
    }
    return i;
}

int convert_to_number(const vl& v, int base) {
    int ret = 0;
    int bases = 1;
    for (int i : v) {
        ret += bases * i;
        bases *= base;
    }
    return ret;
}

int convert_to_number(const int* v, int base, int k) {
    int ret = 0;
    int bases = 1;
    for (int i = 0; i < k; i++) {
        ret += bases * v[i];
        bases *= base;
    }
    return ret;
}

void rebase_array(int baseIn, const int* vIn, int ndIn, int baseOut, int* vOut, int& ndOut) {
    int m = convert_to_number(vIn, baseIn, ndIn); // the incoming number (mostly in base=10...)
    ndOut = convert_to_array(m, baseOut, vOut);
}

bool is_parindrome(const int* v, int k) {
    for (int i = 0; i < (k + 1) / 2; i++) {
        if (v[i] != v[k - i - 1]) {
            return false;
        }
    }
    return true;
}

void find_palindromes(int nd10, int level, int N, int* v10, int k, int* vK, int& sum) {
    int last_level = (nd10 + 1) / 2;
    int ndK = 0;
    if (level == last_level) {
        // now do what you want
        // v10 - a palindrome in base=10
        // convert to the given base k:
        int m = convert_to_number(v10, 10, nd10); // the incoming number (mostly in base=10...)
        ndK = convert_to_array(m, k, vK);
        //rebase_array(10, v10, nd10, k, vK, ndK);

        //print_array(outf, v, dim10);
        bool ispal = is_parindrome(vK, ndK);
        if (ispal) {
            if (m < N) {
                sum += m;
                outf << m << " ; " << sum << endl;
            }
            //cout << m << " ; " << sum << endl;
            //print_array(outf, vK, ndK);
        }
        return;
    }
    for (int digit = level == 0 ? 1 : 0; digit < 10; digit++) {
        v10[level] = digit;
        v10[nd10 - level - 1] = v10[level];
        find_palindromes(nd10, level + 1, N, v10, k, vK, sum);
    }
}

int solve_impl(int N, int k) {
    outf << "k = " << k << endl;
    int sum = 0;
    int ranges[] = { 10,100,1000,10000,100000,1000000 };
    for (int range : ranges) {
        // create the arrays
        const int dim10 = int(log10(range - 1)) + 1;
        const int dimK = int(log10(range - 1) / log10(k)) + 1;
        int* v10 = new int[dim10];
        int* vK = new int[dimK];
        // start looping
        find_palindromes(dim10, 0, N, v10, k, vK, sum);
    }
    return sum;
}

void solve() {
    outf.open("euler36.out");
    auto start = std::chrono::high_resolution_clock::now();

    int N = 77777;
    int k = 2;
    int res = solve_impl(N, k);
    cout << "Answer = " << res << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time = " << t << " s" << endl;
    outf.close();
}

int main() {
    solve();
    return 0;
}
