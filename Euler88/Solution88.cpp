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

struct bres
{
    bres(bool balanced, int p, int s) {
        this->balanced = balanced;
        this->p = p;
        this->s = s;
    }
    bool balanced;
    int p;
    int s;
};

/// <summary>
/// Tries to balance the array so that the product is equal to the sum.
/// </summary>
/// <param name="k">Number of the terms.</param>
/// <param name="a">The array.</param>
/// <param name="i">Incremented term.</param>
/// <param name="j">Reduced term.</param>
bres balance(int k, int* a, int i, int j) {
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
    return bres(balanced, p, s);
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

    // start balancing with the balance (1,2)
    int incr = 2; // incremented index, start with adding 2-s
    int decr = 1; // decremented index
    int incrprev = incr;
    int decrprev = decr;
    int aincrprev = a[incr];
    int adecrprev = a[decr];

    // start balancing and loop until balance is reached
    bres res = balance(k, a, incr, decr);
    while (!res.balanced) {

        // not balanced, i.e. product < sum
        // Options:
        // 1) some adding elements were succesfully added (for example 1...1 -> 1...12...2)
        //    In this case we want to go further, and start balancing the next elements like:
        //    1...12...2 -> 1...12...23...3
        // 2) no elements were added (1...1 -> 1...1 or 1...12...2 -> 1...12...2) 
        //    because even one new element breaks the balance (so that product becomes > sum)
        //    In this case we can't increment adding element, and all we can do
        //    is go back to the previos indexes and reduce number of the greater element
        //    For example if we have n1 ones and n2 twos: 1...12...2, make n1++ and n2--
        //    and try adding 3 again.
        //    Note that we can do that if n2 > 1.
        //    If n2 = 1, try to increment the elements iself and balance with (1,3) instead of (1,2)

        if (a[incr] == aincrprev) { // no elements were inserted, get back

            if (a[decr] > 1) {
                incr = incrprev;
                decr = decrprev;
                a[incr]--;
                a[decr]++;
            }
            else {

            }


            incr = incrprev;
            decr = decrprev;
            a[incr]++;
            a[decr]--;
        }
        else { // some i were inserted succesfully
            incr++;
            decr++;
        }
        incrprev = incr;
        decrprev = decr;
        aincrprev = a[incr];
        adecrprev = a[decr];

        // re-balance
        res = balance(k, a, incr, decr);
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
