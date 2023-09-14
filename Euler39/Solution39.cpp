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
void solve_ab(li pmax) {
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
            if (p <= pmax) {
                // p is the perimeter of the primitive triple, we need all the multiplications up to pmax
                li ntriplesp = pmax / p;
                n++;
                //outf << n << ": a = " << a << " b = " << b << " x = " << x << " y = " << y << " z = " << z << " P = " << p << " N = " << ntriplesp << endl;
                for (li it = 1; it <= ntriplesp; it++) {
                    ntriples[p * it]++;
                }
            }
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

    solve_ab(dim - 1);
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
