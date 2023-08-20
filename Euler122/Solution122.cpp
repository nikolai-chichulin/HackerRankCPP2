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

void outarr(string s, vector<int>& v) {
    cout << s;
    for (int i : v) {
        cout << " " << i;
    }
    cout << endl;
}

void outarr(ofstream& ostr, string s, vector<int>& v) {
    ostr << s;
    for (int i : v) {
        ostr << " " << i;
    }
    ostr << endl;
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

    // for k=1 no steps are needed
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
                outarr("powers of k: ", vout);
            }
            return;
        }
        // call the function recursively
        if (steps < minsteps) {
            getmBF03(k, vout);
        }
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.4.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF04(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;

    // for k=1 no steps are needed
    if (k == 1) {
        return vector<int> {1};
    }

    // even numbers can be factorized like: k = base * 2^addsteps
    if (k % 2 == 0) {
        int base = k;
        size_t addsteps = 0;
        vector<int> addv;
        while (base % 2 == 0) {
            addv.insert(addv.begin(), base);
            base /= 2;
            addsteps++;
        }
        vector<int> ret = getmBF04(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }
    else {
        size_t size = vin.size(); // size
        vector<int> ret;
        vector<int> vout;
        int vmax = vin[size - 1]; // maximum
        cout << "depth: " << depth << " start of loop. Ini vector size is " << vin.size();
        outarr(" : ", vin);
        for (size_t i = 0; i < size; i++) {
            cout << "depth: " << depth << " i = " << i << endl;
            // new vector = old vector + new term
            vector<int> vnew(vin.begin(), vin.end());
            int newterm = vmax + vin[i]; // new sum
            vnew.push_back(newterm);

            if (newterm < k && size < iminsteps) { // continue
                // call the function recursively
                vout = getmBF04(k, vnew, iminsteps, depth);
            }
            else if (newterm == k) { // found the solution
                cout << "Found the factorization vector: ";
                outarr("", vnew);
                vout = vnew;
            }
            else if (newterm > k) { // break the loop
                break;
            }

            size_t steps = vout.size() - 1;  // steps
            if (steps < iminsteps) {
                //cout << "Found the factorization with " << steps << " steps!" << endl;
                //outarr("powers of k: ", vout);
                iminsteps = steps;
                ret = vout;
            }
        }
        cout << "depth: " << depth << " end of loop " << endl;
        return ret;
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.5.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF05(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;

    // for k=1 no steps are needed
    if (k == 1) {
        return vector<int> {1};
    }

    // even numbers can be factorized like: k = base * 2^addsteps
    if (k % 2 == 0) {
        int base = k;
        size_t addsteps = 0;
        vector<int> addv;
        while (base % 2 == 0) {
            addv.insert(addv.begin(), base);
            base /= 2;
            addsteps++;
        }
        vector<int> ret = getmBF05(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }
    else {
        size_t size = vin.size(); // size
        vector<int> ret;
        int vmax = vin[size - 1]; // maximum
        //cout << "depth: " << depth << " start of loop. Ini vector size is " << vin.size();
        //outarr(" : ", vin);
        for (size_t i = 0; i < size; i++) {
            //cout << "depth: " << depth << " i = " << i << endl;
            // new vector = old vector + new term
            vector<int> vnew(vin.begin(), vin.end());
            int newterm = vmax + vin[i]; // new sum
            vnew.push_back(newterm);

            bool dorecursion = newterm < k&& size < iminsteps;
            if (newterm == k || dorecursion) {
                vector<int> vout;
                if (dorecursion) {
                    // call the function recursively
                    vout = getmBF05(k, vnew, iminsteps, depth);
                }
                else if (newterm == k) { // found the solution
                    //cout << "Found the factorization vector: ";
                    //outarr("", vnew);
                    vout = vnew;
                }
                size_t steps = vout.size() - 1;  // steps
                if (steps < iminsteps) {
                    //cout << "Found the factorization with " << steps << " steps!" << endl;
                    //outarr("powers of k: ", vout);
                    iminsteps = steps;
                    ret = vout;
                }
            }
            else {
                break;
            }
        }
        //cout << "depth: " << depth << " end of loop " << endl;
        return ret;
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brure force v.0.6.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF06(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;

    // for k=1 no steps are needed
    if (k == 1) {
        return vector<int> {1};
    }

    // even numbers can be factorized like: k = base * 2^addsteps
    if (k % 2 == 0) {
        int base = k;
        size_t addsteps = 0;
        vector<int> addv;
        while (base % 2 == 0) {
            addv.insert(addv.begin(), base);
            base /= 2;
            addsteps++;
        }
        vector<int> ret = getmBF06(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }
    else {
        size_t size = vin.size(); // size
        vector<int> ret;
        int vmax = vin[size - 1]; // maximum
        //cout << "depth: " << depth << " start of loop. Ini vector size is " << vin.size();
        //outarr(" : ", vin);
        for (size_t i = 0; i < size; i++) {
            //cout << "depth: " << depth << " i = " << i << endl;
            // new vector = old vector + new term
            vector<int> vnew(vin.begin(), vin.end());
            int newterm = vmax + vin[i]; // new sum
            vnew.push_back(newterm);

            bool dorecursion = newterm < k&& size < iminsteps;
            if (size == iminsteps - 1) {
                //cout << "I'm here" << endl;
                dorecursion &= (vin[0] + vmax) <= k && (2 * vmax >= k);
            }
            else if (size == iminsteps - 2) {
                //cout << "I'm here" << endl;
                dorecursion &= (vin[0] + 2 * vmax) <= k && (4 * vmax >= k);
            }
            else if (size == iminsteps - 3) {
                //cout << "I'm here" << endl;
                dorecursion &= (vin[0] + 3 * vmax) <= k && (8 * vmax >= k);
            }

            if (newterm == k || dorecursion) {
                vector<int> vout;
                if (dorecursion) {
                    // call the function recursively
                    vout = getmBF06(k, vnew, iminsteps, depth);
                }
                else if (newterm == k) { // found the solution
                    //cout << "Found the factorization vector: ";
                    //outarr("", vnew);
                    vout = vnew;
                }
                size_t steps = vout.size() - 1;  // steps
                if (steps < iminsteps) {
                    //cout << "Found the factorization with " << steps << " steps!" << endl;
                    //outarr("powers of k: ", vout);
                    iminsteps = steps;
                    ret = vout;
                }
            }
            else {
                break;
            }
        }
        //cout << "depth: " << depth << " end of loop " << endl;
        return ret;
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

    minsteps = 20;
    int k = 199;
    vector<int> v = { 1 };
    getmBF03(k, v);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << minsteps << endl;
}

void solveBF004() {
    auto start = std::chrono::high_resolution_clock::now();

    int k = 19;
    vector<int> vin = { 1 };
    vector<int> vout = getmBF04(k, vin, 20, 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << vout.size() - 1 << endl;
    outarr("powers of k: ", vout);
}

void solveBF005() {
    auto start = std::chrono::high_resolution_clock::now();

    int k = 199;
    vector<int> vin = { 1 };
    vector<int> vout = getmBF05(k, vin, 20, 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << vout.size() - 1 << endl;
    outarr("powers of k: ", vout);
}

void solveBF006() {
    auto start = std::chrono::high_resolution_clock::now();

    size_t minstepsini = 20;
    int k = 199;
    vector<int> vin = { 1 };
    vector<int> vout = getmBF06(k, vin, minstepsini, 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << vout.size() - 1 << endl;
    outarr("powers of k: ", vout);
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
        //vector<int> v = { 1 };
        //minsteps = 20; // initial steps
        //getmBF03(k, v);
        //s += minsteps;
        //cout << " M(" << k << ") = " << minsteps << " S = " << s << endl;
        //outf << " M(" << k << ") = " << minsteps << " S = " << s << endl;
        vector<int> vin = { 1 };
        vector<int> vout = getmBF06(k, vin, 20, 0);
        s += vout.size() - 1;
        cout << " M(" << k << ") = " << vout.size() - 1 << " S = " << s;
        outf << " M(" << k << ") = " << vout.size() - 1 << " S = " << s;
        outarr(" powers of k: ", vout);
        outarr(outf, " powers of k: ", vout);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    outf << "Execution time    = " << t << " s" << endl;
    outf.close();
}

int main() {

    solveAll();
    //solveBF();
    //solveBF004();
    //solveBF005();
    //solveBF006();

    return 0;
}