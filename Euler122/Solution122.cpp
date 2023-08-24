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

int nbinaries = 0;
int ncalls = 0;
int nrecursion = 0;

int base[][6] = { {},{},{ 2 },{ 2,3 },{},{ 2,4,5 },{},{ 2,3,4,7 },{},{2,4,8,9} };

const vector<int> vempty = { };
const vector<int> vone = { 1 };
const vector<int> vtwo = { 1,2 };
const vector<int> vthree = { 1,2,3 };
const vector<int> vfour = { 1,2,4 };

/// <summary>
/// Prints the answer as a string like n^a * n^b = n^c etc.
/// </summary>
/// <param name="ostr"></param>
/// <param name="v"></param>
void printpowers(ofstream& ostr, vector<int>& v) {
    for (size_t i = 1; i < v.size(); i++) {
        ostr << "n^" << v[i - 1] << " * n^" << v[i] - v[i - 1] << " = n^" << v[i] << endl;
    }
}

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
/// Brute force v.0.0.
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
/// Brute force v.0.1.
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
/// Brute force v.0.3.
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
/// Brute force v.0.4.
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
/// Brute force v.0.5.
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
/// Brute force v.0.6.
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

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brute force v.0.7.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF07(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;
    ncalls++;

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
        vector<int> ret = getmBF07(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }
    else {
        vector<int> ret;
        size_t size = vin.size(); // size
        int vmax = vin[size - 1]; // maximum

        if (size < iminsteps) {
            // check the possibility to complete the sequence in one move
            // given we have a series of known powers a0, a1, ..., aN
            // new term can be: aN+a0, aN+a2, ..., aN+aN
            // is k in this range? if yes, we can get reach the target in one act
            bool stop = std::binary_search(vin.begin(), vin.end(), k - vmax);

            if (stop) {
                vector<int> vnew(vin.begin(), vin.end());
                vnew.push_back(k);
                if (size < iminsteps) {
                    iminsteps = size;
                }
                //cout << "1) Found the factorization with " << size << " steps (binary search): ";
                //outarr("", vnew);
                return vnew;
            }
            else { // use recursion
                //cout << "depth: " << depth << " start of the loop. Ini vector size is " << vin.size();
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
                        dorecursion &= std::binary_search(vnew.begin(), vnew.end(), k - newterm);
                        //dorecursion &= (vin[0] + vmax) <= k && (2 * vmax >= k);
                    }
                    else if (size == iminsteps - 2) {
                        //cout << "I'm here. dorecirsion is " << dorecursion;
                        dorecursion &= (vin[0] + 2 * vmax) <= k && (4 * vmax >= k);
                        //cout << " now dorecirsion is " << dorecursion << endl;
                    }
                    else if (size == iminsteps - 3) {
                        //cout << "I'm here" << endl;
                        dorecursion &= (vin[0] + 3 * vmax) <= k && (8 * vmax >= k);
                    }

                    if (newterm == k || dorecursion) {
                        vector<int> vout;
                        if (dorecursion) {
                            // call the function recursively
                            nrecursion++;
                            vout = getmBF07(k, vnew, iminsteps, depth);
                        }
                        else if (newterm == k) { // found the solution
                            vout = vnew;
                        }
                        size_t steps = vout.size() - 1;  // steps
                        if (steps < iminsteps) {
                            //cout << "2) Found the factorization with " << steps << " steps (recursion): ";
                            //outarr("", vout);
                            iminsteps = steps;
                            ret = vout;
                        }
                    }
                    else {
                        break;
                    }
                }
                //cout << "depth: " << depth << " end of loop " << endl;
            }
        }
        return ret;
    }
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brute force v.0.8.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF08(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;
    ncalls++;

    // guard
    if (vin.empty()) {
        return vempty;
    }

    // return constant vectors for k=1,2,3,4
    if (k == 1) {
        return vone;
    }
    else if (k == 2) {
        return vtwo;
    }
    else if (k == 3) {
        return vthree;
    }
    else if (k == 4) {
        return vfour;
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
        vector<int> ret = getmBF08(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }

    // odd numbers, the most sofisticated case
    size_t size = vin.size(); // size

    // the steps count for the initial array is size-1
    // steps count after adding a number to the vin is equal to size
    // we are only interested in cases with less steps
    if (size >= iminsteps) {
        return vempty;
    }

    // calculate we can the reserve of elements that potentially can be added to Vin
    size_t nres = iminsteps - size; // > 0
    // then the maximal of the last added element is Vmax * 2^nres
    int vmax = vin[size - 1]; // maximum of vin
    int vlastmax = vmax * int(pow(2, nres));

    if (vlastmax < k) {
        return vempty;
    }

    // now check if we can complete the sequence in one move ("close" the array)
    // given we have a series of known powers v0, v1, ..., vN
    // the new element can be one of the following: vN+v0, vN+v2, ..., vN+vN
    // is k equal to any of them? if yes, we can get reach the target right now
    nbinaries++;
    if (std::binary_search(vin.begin(), vin.end(), k - vmax)) {
        vector<int> ret(vin.begin(), vin.end());
        ret.push_back(k); // the final array
        if ((ret.size() - 1) < iminsteps) {
            iminsteps = ret.size() - 1;
        }
        return ret;
    }

    // add the array elements to the last element one by one
    // it only makes sense if the array is greater than
    if (size + 1 >= iminsteps) {
        return vempty;
    }
    vector<int> ret = vempty;
    for (int vi : vin) {
        int newelement = vmax + vi; // new sum vN + vi
        if (newelement > k) { // do not exceed the k
            break;
        }

        // construct the new vector = old vector + new element
        vector<int> vnew(vin.begin(), vin.end());
        vnew.push_back(newelement);

        // there are two options:
        // 1) the new array can be "closed" by adding one element right here, or
        // 2) pass the new array as a parameter to the recursion

        // 1)
        nbinaries++;
        if (std::binary_search(vnew.begin(), vnew.end(), k - newelement)) {
            vnew.push_back(k);
            ret = vnew;
            if ((ret.size() - 1) < iminsteps) {
                iminsteps = ret.size() - 1;
            }
            break;
        }

        // 2)
        // the vnew array can't be closed by adding only one element (see step 1)
        // so it can be closed by adding two or more elements inside the recursive call
        // but in this case nsteps can be size(vnew) + 1 in the best case
        // so it only makes sense if size(vnew) + 1 < iminsteps that is reached so far
        // but size(vnew) = size(vin) + 1
        // thus:
        if (size + 2 < iminsteps) {
            nrecursion++;
            vector<int> tmp = getmBF08(k, vnew, iminsteps, depth);
            if (!tmp.empty() && (tmp.size() - 1) < iminsteps) {
                iminsteps = tmp.size() - 1;
                ret = tmp;
            }
        }
    }
    //cout << "depth: " << depth << " end of loop " << endl;
    return ret;
}

/// <summary>
/// Returns the minimal sequence of terms to get the given number k.
/// Brute force v.0.8.1.
/// </summary>
/// <param name="k">Current k</param>
/// <param name="vin">Available terms</param>
vector<int> getmBF081(int k, vector<int>& vin, size_t iminsteps, int depth) {

    depth++;
    ncalls++;

    // guard
    if (vin.empty()) {
        return vempty;
    }

    // return constant vectors for k=1,2,3,4
    if (k == 1) {
        return vone;
    }
    else if (k == 2) {
        return vtwo;
    }
    else if (k == 3) {
        return vthree;
    }
    else if (k == 4) {
        return vfour;
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
        vector<int> ret = getmBF081(base, vin, iminsteps, depth); // decomposition of the odd base
        // now concatenate the two vectors
        for (int a : addv) {
            ret.push_back(a);
        }
        return ret;
    }

    // odd numbers, the most sofisticated case
    size_t size = vin.size(); // size

    // calculate the reserve of elements that potentially can be added to Vin
    // it must be > 0, otherwise quit
    int nres = int(iminsteps) - int(size);
    if (nres <= 0) {
        return vempty;
    }

    // then the maximum of the last added element is Vmax * 2^nres
    // if the maximum is less than k, quit
    int vmax = vin[size - 1]; // maximum of vin
    int vlastmax = vmax * int(pow(2, nres));
    if (vlastmax < k) {
        return vempty;
    }

    nres--; // in the loop below the array wil be one element longer, so decrement nres
    vector<int> ret = vempty;
    for (int vi : vin) {
        int newelement = vmax + vi; // new sum vN + vi
        if (newelement > k) { // do not exceed the k
            break;
        }

        // estimate again the maximum of the last added element is Vmax * 2^nres
        // if the maximum is less than k, continue the loop
        vlastmax = newelement * int(pow(2, nres));
        if (vlastmax < k) {
            continue;
        }

        // construct the new vector = old vector + new element
        vector<int> vnew(vin.begin(), vin.end());
        vnew.push_back(newelement);
        //outf << "depth = " << depth << " vi = " << vi;
        //outarr(outf, " Vnew: ", vnew);

        // there are two options:
        // 1) the new array can be "closed" by adding one element right here, or
        // 2) pass the new array as a parameter to the recursion

        // 1)
        if (newelement >= k / 2) {
            //outf << "depth = " << depth << " binary search in the series";
            //outarr(outf, " Vnew: ", vnew);
            nbinaries++;
            if (std::binary_search(vnew.begin(), vnew.end(), k - newelement)) {
                vnew.push_back(k);
                ret = vnew;
                if ((ret.size() - 1) < iminsteps) {
                    iminsteps = ret.size() - 1;
                }
                //outf << "--------------------" << endl;
                //outf << "depth = " << depth << " the series found. Steps = " << iminsteps << endl;
                //outarr(outf, "Vin:          ", vin);
                //outarr(outf, "Vnew:         ", vnew);
                //outarr(outf, "Final powers: ", ret);
                //outf << "--------------------" << endl;
                break;
            }
        }

        // 2)
        // the vnew array can't be closed by adding only one element (see step 1)
        // so it can be closed by adding two or more elements inside the recursive call
        // but in this case nsteps can be size(vnew) + 1 in the best case
        // so it only makes sense if size(vnew) + 1 < iminsteps that is reached so far
        // but size(vnew) = size(vin) + 1
        // thus:
        if (size + 2 < iminsteps) {
            nrecursion++;
            vector<int> tmp = getmBF081(k, vnew, iminsteps, depth);
            if (!tmp.empty() && (tmp.size() - 1) < iminsteps) {
                iminsteps = tmp.size() - 1;
                ret = tmp;
            }
        }
    }
    //cout << "depth: " << depth << " end of loop " << endl;
    return ret;
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

void solveBF007() {
    auto start = std::chrono::high_resolution_clock::now();

    ncalls = 0;
    nrecursion = 0;
    size_t minstepsini = 20;
    int k = 199;
    vector<int> vin = { 1 };
    vector<int> vout = getmBF07(k, vin, minstepsini, 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "v.0.7 Execution time    = " << t << " s" << endl;
    cout << "M(" << k << ") = " << vout.size() - 1 << endl;
    outarr("powers of k: ", vout);
    cout << "N function calls   = " << ncalls << endl;
    cout << "N recursive calls  = " << nrecursion << endl;
}

void solveBF008() {
    outf.open("test.dat");
    auto start = std::chrono::high_resolution_clock::now();

    ncalls = 0;
    nrecursion = 0;
    size_t minstepsini = 20;
    int k = 199;
    vector<int> vin = { 1 };
    vector<int> vout = getmBF081(k, vin, minstepsini, 0);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "v.0.8 Execution time    = " << t << " s" << endl;
    size_t steps = vout.empty() ? 0 : vout.size() - 1;
    cout << "M(" << k << ") = " << steps << endl;
    if (steps > 0) {
        outarr("Powers of k: ", vout);
    }
    cout << "N binary searches  = " << nbinaries << endl;
    cout << "N function calls   = " << ncalls << endl;
    cout << "N recursive calls  = " << nrecursion << endl;
    outf.close();
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
    for (int k = 2; k <= 200; k++) {
        //vector<int> v = { 1 };
        minsteps = 15; // initial steps
        //getmBF03(k, v);
        //s += minsteps;
        //cout << " M(" << k << ") = " << minsteps << " S = " << s << endl;
        //outf << " M(" << k << ") = " << minsteps << " S = " << s << endl;
        vector<int> vin = { 1,2 };
        vector<int> vout = getmBF081(k, vin, minsteps, 0);
        s += vout.size() - 1;
        //cout << " M(" << k << ") = " << vout.size() - 1 << " S = " << s;
        outf << " M(" << k << ") = " << vout.size() - 1 << " S = " << s;
        //outarr(" powers of k: ", vout);
        outarr(outf, " powers of k: ", vout);
        printpowers(outf, vout);
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
    //solveBF007();
    //solveBF008();
    //solveBF008();

    return 0;
}