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

const li dim = 5000001;

li ntriples[dim] = {}; // ntriples[p] = number of triples for the given perimeter p
li maxtriples_perimeter[dim] = {}; // maxtriples_perimeter[p] = perimeter with maximum triples less or equal than the given p

void print_array(ostream& ostr, const int* v, int k) {
    for (int i = 0; i < k; i++) {
        ostr << v[i] << " ";
    }
    ostr << endl;
}

/// <summary>
/// Constructs the ntriples array.
/// </summary>
/// <param name="pmax">The maximal acceptable perimeter.</param>
void solve_ab_v0(li pmax) {
    int n = 0;
    li amax = 2500; // li(sqrt(pmax)) + 1;
    for (li a = 3; a < amax; a += 2) {
        li a_2 = a * a;
        for (li b = 1; b < a; b += 2) {
            li b_2 = b * b;
            li x = a * b;
            li y = (a_2 - b_2) / 2;
            li z = (a_2 + b_2) / 2;
            li p = x + y + z;
            //outf << n << ": a = " << a << " b = " << b << " x = " << x << " y = " << y << " z = " << z << " P = " << p << " N = " << ntriplesp << endl;
            // p is the perimeter of the primitive triple, we need all the multiplications up to pmax
            li pp = p;
            while (pp <= pmax) {
                ntriples[pp]++;
                pp += p;
            }
        }
    }
}

li getgcd(li d1, li d2) {
    li a = d1 > d2 ? d1 : d2; // max
    li b = (a == d1) ? d2 : d1; // min
    while (b != 0) {
        li t = b;
        b = a % b;
        a = t;
    }
    return a;
}

bool arevalid(li a, li b) {
    if (a % 2 != 0 && b % 2 != 0) { // not both odd
        return false;
    }
    li gcd = getgcd(a, b);
    if (gcd > 1) {
        return false;
    }
    return true;
}

/// <summary>
/// Constructs the ntriples array.
/// </summary>
/// <param name="pmax">The maximal acceptable perimeter.</param>
void solve_ab_v1(li pmax) {
    int n = 0;
    li amax = 2500; // li(sqrt(pmax)) + 1;
    for (li a = 1; a < amax; a++) {
        li a_2 = a * a;
        for (li b = 1; b < a; b++) {
            if (!arevalid(a, b)) {
                continue;
            }
            n++;
            li b_2 = b * b;
            li x = 2 * a * b;
            li y = (a_2 - b_2);
            li z = (a_2 + b_2);
            li p = x + y + z;
            // p is the perimeter of the primitive triple, we need all the multiplications up to pmax
            li pp = p;
            while (pp <= pmax) {
                ntriples[pp]++;
                pp += p;
            }
            outf << n << ": a = " << a << " b = " << b << " x = " << x << " y = " << y << " z = " << z << " P = " << p << endl;
        }
    }
}

/// <summary>
/// Constructs the maxtriples_perimeter array.
/// </summary>
/// <param name="pmax">The maximal acceptable perimeter.</param>
void finalize(li pmax) {
    li p_with_max_triples = 0;
    li ntriples_max = 0;
    for (li p = 0; p <= pmax; p++) {
        if (ntriples[p] > ntriples_max) {
            ntriples_max = ntriples[p];
            p_with_max_triples = p;
        }
        maxtriples_perimeter[p] = p_with_max_triples;
        //outf << p << " " << ntriples[p] << " " << maxtriples_perimeter[p] << " " << ntriples_max << endl;
    }
}

void solve() {
    outf.open("euler39.out");
    auto start = std::chrono::high_resolution_clock::now();

    solve_ab_v1(dim - 1);
    finalize(dim - 1);
    cout << maxtriples_perimeter[5000000] << endl;

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
