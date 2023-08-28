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

int irecursion = 0;

void outarr(ostream& ostr, string s, const int* v, int k) {
    ostr << s;
    for (int i = 0; i < k; i++) {
        ostr << " " << v[i];
    }
    ostr << endl;
}

void fillup(int k, int* a) {
    a[0] = 0;
    a[1] = k;
    for (int i = 2; i <= k; i++) {
        a[i] = 0;
    }
}

void fillup(int k, int* a, int v) {
    for (int i = 0; i < k; i++) {
        a[i] = v;
    }
}

int* getdirectarray(int k, const int* a) {
    int* ret = new int[k];
    int l = 0;
    for (int i = 0; i < k; i++) {
        ret[i] = 0;
    }
    for (int i = 0; i < k; i++) {
        if (a[i] > 0) {
            for (int j = 0; j < a[i]; j++) {
                ret[l] = i;
                l++;
            }
        }
    }
    return ret;
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

int getproductdir(int k, const int* a) {
    int ret = 1;
    for (int i = 0; i < k; i++) {
        ret *= a[i];
    }
    return ret;
}

int getsumdir(int k, const int* a) {
    int ret = 0;
    for (int i = 0; i < k; i++) {
        ret += a[i];
    }
    return ret;
}

struct bres
{
    bres(bool balanced, int p, int s, int replaced) {
        this->balanced = balanced;
        this->p = p;
        this->s = s;
        this->replaced = replaced;
    }
    bool balanced;
    int p;
    int s;
    int replaced;
};

/// <summary>
/// Tries to balance the array so that the product is equal to the sum.
/// </summary>
/// <param name="k">Number of the terms.</param>
/// <param name="a">The initial array.</param>
/// <param name="i">Incremented element.</param>
/// <param name="j">Decremented element.</param>
bres balance(int k, int* a, int i, int j) {
    bool output = false;
    bool balanced = false;
    int p = getproduct(k, a);
    int s = getsum(k, a);
    int pprev = p;
    int sprev = s;
    int replaced = 0;
    while (true) {
        if (p > s) {
            replaced--;
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
        if (a[j] == 0) {
            break;
        }
        replaced++;
        a[i]++;
        a[j]--;
        pprev = p;
        sprev = s;
        p = getproduct(k, a);
        s = getsum(k, a);
    }
    if (output) {
        if (balanced) {
            cout << "Balanced:" << endl;
        }
        else {
            cout << "Not balanced:" << endl;
        }
        cout << "a[" << i << "] = " << a[i] << endl;
        cout << "a[" << j << "] = " << a[j] << endl;
        cout << "P = " << p << "; S = " << s << endl;
        cout << "Replaced " << replaced << " elements" << endl;
    }
    return bres(balanced, p, s, replaced);
}

/// <summary>
/// Spins all elements starting with l-th.
/// </summary>
/// <param name="k"></param>
/// <param name="a"></param>
/// <param name="l"></param>
/// <returns></returns>
bool spin(int k, int* a, int l, int depth) {
    depth++;
    irecursion++;
    for (int i = a[l - 1]; i < k; i++) {
        a[l] = i;
        outf1 << "l = " << l << " a[l] = " << i << endl;
        // recursive call for all the elements but the last one
        if (l < k - 1) {
            outf1 << "recursive call..." << endl;
            if (spin(k, a, l + 1, depth)) {
                outf1 << "return true" << endl;
                return true;
            }
        }
        else { // estimate the product and sum for the last element only!
            outf1 << "the last element!" << endl;
            outarr(outf1, "Array: ", a, k);
            int p = getproductdir(k, a);
            int s = getsumdir(k, a);
            outf1 << "p = " << p << " s = " << s << endl;
            if (p == s) {
                outf1 << "found the number, return true" << endl;
                return true;
            }
            else if (p > s) {
                outf1 << "p > s, break" << endl;
                break;
            }
        }
    }
    outf1 << "return false" << endl;
    return false;
}

/// <summary>
/// Recursively spins all elements of the given array starting with l-th.
/// </summary>
/// <param name="k">The original k.</param>
/// <param name="length">The actual length of the given array.</param>
/// <param name="a">The shortened array of elements.</param>
/// <param name="l">The starting index to spin.</param>
/// <param name="depth">Recursion depth.</param>
/// <param name="addition">The number of ones.</param>
/// <returns></returns>
bool spin_v01(int k, int length, int* a, int l, int depth, int addition) {
    depth++;
    irecursion++;
    int istart = l == 0 ? 2 : a[l - 1];
    for (int i = istart; i <= k; i++) {
        a[l] = i;
        outf1 << "l = " << l << " a[l] = " << i << endl;
        // recursive call for all the elements but the last one
        if (l < length - 1) {
            // before the recursive call we can do an estimate of the product and sum
            int p = getproductdir(length, a);
            int s = getsumdir(length, a) + addition;
            if (p > s) {
                outf1 << "p > s, break on depth = " << depth << endl;
                break;
            }
            outf1 << "recursive call..." << endl;
            if (spin_v01(k, length, a, l + 1, depth, addition)) {
                outf1 << "found the array!" << endl;
                return true;
            }
        }
        else { // estimate the product and sum for the last element only!
            outf1 << "the last element!" << endl;
            outarr(outf1, "Array: ", a, length);
            int p = getproductdir(length, a);
            int s = getsumdir(length, a) + addition;
            outf1 << "p = " << p << " s = " << s << endl;
            if (p == s) {
                outf1 << "found the number, return true" << endl;
                return true;
            }
            else if (p > s) {
                outf1 << "p > s, break on depth = " << depth << endl;
                break;
            }
        }
    }
    a[l] = 2; // back to the minimum
    outf1 << "return false" << endl;
    return false;
}

void solve(int k) {

    //outf1.open("test1.out");
    //outf2.open("test2.out");
    //outf3.open("test3.out");

    auto start = std::chrono::high_resolution_clock::now();

    // error code
    int err = 0;

    // initial array
    int* a = new int[k + 1];
    fillup(k, a); // initial fill-up with 1-s

    // start balancing with the balance (1,2)
    int incr = 2; // incremented index, start with adding 2-s
    int decr = 1; // decremented index
    int incrprev = incr;
    int decrprev = decr;
    int incrprevprev = incrprev;
    int decrprevprev = decrprev;
    int aincrprev = a[incr];
    int adecrprev = a[decr];

    // start balancing and loop until balance is reached
    bres res = balance(k, a, incr, decr);
    while (!res.balanced) {

        // not balanced, i.e. product < sum
        // Options:
        // 1) Count of the replace elements > 1 (for example 1...1 -> 1...12...2)
        //    In this case we want to go further, and start balancing the next elements like:
        //    1...12...2 -> 1...12...23...3
        // 2) Only one element or no elements were replaced 
        //    (for example 1...1 -> 1...1 or 1...12...2 -> 1...12...2) 
        //    In this case all we can do is go back to the previos indexes,
        //    reduce number of the greater element and try to balance again.
        //    For example if we have n1 ones and n2 twos: 1...12...2, make n1++ and n2--
        //    and try adding 3 again.
        //    Note that we can do that if n2 > 1.
        //    If n2 = 1, try to increment the element iself and balance with (1,3) instead of (1,2)

        if (adecrprev == 1) {
            if (res.replaced == 0) {
                err = 1; // not balanced, quit
                break;
            }
            else { // try the next element
                decrprev = decr;
                incr++;
                decr++;
            }
        }
        else if (adecrprev > 1) {
            if (res.replaced == 0) {
                a[decr]--;
                a[decrprev]++;
            }
            else { // try the next element
                decrprev = decr;
                incr++;
                decr++;
            }
        }
        else {
            err = 2; // we shouldn't come here, something wierd happened, quit
            break;
        }

        //if (res.replaced <= 1) {
        //    if (a[decr] > 1) {
        //        a[decr]--;
        //        a[decrprev]++;
        //    }
        //    else {
        //        a[decr] = 0;
        //        a[decrprevprev]++;
        //        incr = incrprev;
        //        decr = decrprev;
        //        incrprev = incrprevprev;
        //        decrprev = decrprevprev;
        //    }
        //    //incr = incrprev;
        //    //decr = decrprev;
        //    //a[incr]++;
        //    //a[decr]--;
        //}
        //else { // some i were inserted succesfully
        //    incrprevprev = incrprev;
        //    decrprevprev = decrprev;
        //    incrprev = incr;
        //    decrprev = decr;
        //    incr++;
        //    decr++;
        //}
        //aincrprev = a[incr];
        adecrprev = a[decr];

        // re-balance
        res = balance(k, a, incr, decr);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "N(" << k << ") = " << res.p << endl;
    cout << "a: ";
    for (int i = 1; i < k; i++) {
        if (a[i] > 0) {
            cout << a[i] << " ";
        }
    }
    cout << endl;
    cout << "Execution time    = " << t << " s" << endl;
    //outf1 << "Execution time    = " << t << " s" << endl;

    //outf1.close();
    //outf2.close();
    //outf3.close();
    delete[] a;
}

void solveBF_v01(int k) {

    if (k == 1) {
        cout << "N(" << k << ") = " << 1 << endl;
        outf1 << "N(" << k << ") = " << 1 << endl;
        return;
    }

    outf1.open("test1.out");
    //outf2.open("test2.out");
    //outf3.open("test3.out");

    auto start = std::chrono::high_resolution_clock::now();

    // initial array of multipliers counts
    int* multipliers = new int[k + 1];
    fillup(k, multipliers); // initially only 1-s

    // maximally fill up the array with twos: 1,... 1, 2,... 2.
    bres res = balance(k, multipliers, 2, 1);

    // now get the shortened array consisted of only added twos: 2...2
    int depth = 0;
    int l = res.replaced; // length
    int addition = k - l; // number of ones which must be added to the sum
    int* shortarray = new int[l];
    fillup(l, shortarray, 2);

    // and call the main function in loop
    bool ret = true;
    while (!spin_v01(k, l, shortarray, 0, depth, addition)) {
        outf1 << "Shortened the array!" << endl;
        delete[] shortarray;
        l--;
        if (l == 1) {
            ret = false;
            break;
        }
        addition++;
        shortarray = new int[l];
        fillup(l, shortarray, 2);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    if (ret) {
        int s = getsumdir(l, shortarray) + addition;
        cout << "N(" << k << ") = " << s << endl;
        outf1 << "N(" << k << ") = " << s << endl;
        outarr(outf1, "Final array: ", shortarray, l);
        outarr(cout, "Final array: ", shortarray, l);
        delete[] shortarray;
    }
    else {
        cout << "N(" << k << ") - unsuccesfull " << endl;
        outf1 << "N(" << k << ") - unsuccesfull " << endl;
    }
    outf1 << endl;
    outf1 << "Ncalls            = " << irecursion << endl;
    outf1 << "Execution time    = " << t << " s" << endl;
    cout << "Execution time    = " << t << " s" << endl;

    outf1.close();
    //outf2.close();
    //outf3.close();

    delete[]  multipliers;
}

int main() {

    for (int k = 12000; k <= 12000; k++) {
        solveBF_v01(k);
    }

    return 0;
}
