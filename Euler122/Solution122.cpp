#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

ofstream outf;

size_t nmin = 10000;
size_t minsteps = 10000;

int base[][6] = { {},{},{ 2 },{ 2,3 },{},{ 2,4,5 },{},{ 2,3,4,7 },{},{2,4,8,9} };

void outarr(vector<int>& v) {
    cout << "vector v: ";
    for (int i : v) {
        cout << " " << i;
    }
    cout << endl;
}

//int getm(int k, int base) {
//}

int getm(int k) {

    if (k == 1) {
        return 0;
    }
    if (k == 2) {
        return 1;
    }
    if (k == 3) {
        return 2;
    }
    if (k == 5) {
        return 3;
    }
    if (k == 7) {
        return 4;
    }
    if (k == 9) {
        return 4;
    }
    if (k == 11) {
        return 5;
    }

    if (k % 2 == 0) {
        // find the base
        int base = k;
        int steps = 0;
        while (base % 2 == 0) {
            base /= 2;
            steps++;
        }
        if (base == 1) {
            base = 2;
            steps--;
        }
        return steps + getm(base);
    }
    else {
        int tmp1 = 1 + getm(k - 1);
        int tmp3 = getm(3) + getm(k - 3);
        int tmp5 = getm(5) + getm(k - 5);
        int tmp7 = getm(7) + getm(k - 7);
        return min(min(min(tmp1, tmp3), tmp5), tmp7);
    }
}

/// <summary>
/// 
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available powers</param>
void getv(int k, vector<int>& vin) {
    vector<int> vout = vin;
    size_t size = vin.size();
    int vmax = vin[size - 1];
    for (size_t i = 0; i < size; i++) {
        int j = vmax + vin[i];
        //cout << vin[i] << " + " << vmax << endl;
        if (j == k) {
            if (vin.size() < nmin)
                nmin = vin.size();
            //cout << "Found the numver, terms - " << vin.size() << endl;
            return;
        }
        vout.push_back(j);
        getv(k, vout);
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.0.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
void getmBF00(int k, vector<int>& vin) {
    size_t size = vin.size(); // size
    int vmax = vin[size - 1]; // maximum
    for (size_t i = 0; i < size; i++) {
        int newterm = vmax + vin[i]; // new sum
        vector<int> vout(vin.begin(), vin.end());
        vout.push_back(newterm); // save it in the array as a new maximum
        //cout << vin[i] << " + " << vmax << endl;
        if (newterm == k) { // if the sum is equal to the target, quit
            if (vout.size() <= nmin) {
                nmin = vout.size();
                cout << "Found the number, N of terms = " << vout.size() << " Nmin = " << nmin << endl;
                outarr(vout);
            }
            return;
        }
        if (newterm > k) {
            return;
        }
        getmBF00(k, vout); // and call recursively
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.1.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
void getmBF01(int k, vector<int>& vin) {
    size_t size = vin.size(); // size
    int vmax = vin[size - 1]; // maximum
    for (size_t i = 0; i < size; i++) {
        int newterm = vmax + vin[i]; // new sum
        if (newterm > k) {
            return;
        }
        vector<int> vout(vin.begin(), vin.end());
        vout.push_back(newterm); // save it in the array as a new maximum
        //cout << vin[i] << " + " << vmax << endl;
        if (newterm == k) { // if the sum is equal to the target, quit
            if (vout.size() <= nmin) {
                nmin = vout.size();
                cout << "Found the number, N of terms = " << vout.size() << " Nmin = " << nmin << endl;
                outarr(vout);
            }
            return;
        }
        getmBF01(k, vout); // and call recursively
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.3.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
void getmBF03(int k, vector<int>& vin) {

    // for n no steps are needed
    if (k == 1) {
        minsteps = 0;
    }

    size_t size = vin.size(); // size
    int vmax = vin[size - 1]; // maximum
    for (size_t i = 0; i < size; i++) {
        int newterm = vmax + vin[i]; // new sum
        if (newterm > k) { // if the new sum is greater than the targett, quit
            return;
        }
        // create a temp vector = the old vector + the new term
        vector<int> vout(vin.begin(), vin.end());
        vout.push_back(newterm);
        size_t steps = vout.size() - 1;  // steps
        //cout << vin[i] << " + " << vmax << endl;
        if (newterm == k) { // if the sum is equal to the target, we found the solution, quit
            if (steps < minsteps) {
                minsteps = steps;
                cout << "Found the factorization with " << minsteps << " steps!" << endl;
                outarr(vout);
            }
            return;
        }
        // call the function recursively
        if (steps < minsteps) {
            getmBF03(k, vout);
        }
    }
}

int getn(int k) {

    if (k == 1) {
        return 0;
    }
    if (k == 2) {
        return 1;
    }
    if (k == 3 || k == 4) {
        return 2;
    }
    if (k == 5) {
        return 3;
    }

    if (k % 2 == 0) {
        return getn(k / 2) + 1;
    }
    int res = getn(k - 1) + 1;
    return res;
}

void solveBF() {
    auto start = std::chrono::high_resolution_clock::now();

    minsteps = 50;
    int k = 200;
    vector<int> v = { 1 };
    getmBF03(k, v);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << minsteps << endl;
}

void solve() {
    auto start = std::chrono::high_resolution_clock::now();

    int k = 211;
    int n = getn(k);
    cout << "N(" << k << ")= " << n << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
}

void solveAll() {
    outf.open("test.dat");
    auto start = std::chrono::high_resolution_clock::now();

    size_t s = 0;
    for (int k = 1; k <= 200; k++) {
        vector<int> v = { 1 };
        minsteps = 50; // initial steps
        getmBF03(k, v);
        s += minsteps;
        cout << " M(" << k << ") = " << minsteps << " S = " << s << endl;
        outf << " M(" << k << ") = " << minsteps << " S = " << s << endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    outf.close();
}

int main() {

    //solveAll();
    solveBF();

    return 0;
}