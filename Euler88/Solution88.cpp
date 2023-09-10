#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>
#include <set>

using namespace std;

ofstream outf;
ofstream outf1, outf2;

const int pmax = numeric_limits<int>::max();
const int dim_k = 210000;
const int dim_div = 100;

set<int> kset;
int nmin[dim_k + 1] = {};
int ncalls[dim_div] = {};
int ncallsall = 0;

int kmin = 1000000;
int kmax = 0;

struct result
{
    result() {
        this->found = false;
        this->number = 0;
        this->count = 0;
    }
    result(bool found, int number, int count) {
        this->found = found;
        this->number = number;
        this->count = count;
    }
    bool found; // found or not
    int number; // the product-sum number
    int count; // non-unity elements
};

void array_nonzero_print(ostream& ostr, string s, const int* v, int k) {
    ostr << s;
    for (int i = 0; i < k; i++) {
        if (v[i] > 0)
            ostr << " " << v[i];
    }
    ostr << endl;
}

void array_nonzero_print2(ostream& ostr, string s, const int* v, int k) {
    for (int i = 0; i < k; i++) {
        if (v[i] > 0) {
            ostr << i << " " << v[i] << endl;
        }
    }
    ostr << endl;
}

void set_print(ostream& ostr, string s, const set<int>& v) {
    ostr << s;
    for (int i : v) {
        ostr << i << endl;
    }
    ostr << endl;
}

result f(int k, int l, int pprev, int sprev, int level, int aprev, int countprev, bool output) {
    level++;
    result ret(false, pmax, countprev);

    if (level == l) {
        if (pprev > 1) {
            if (sprev % (pprev - 1) == 0) {
                int x = sprev / (pprev - 1);
                if (x >= aprev) {
                    int p = pprev * x;
                    ret.found = true;
                    ret.number = p;
                    ret.count = countprev + 1;
                    outf << "Level " << level << " found a product-sum number " << p << " = ... " << aprev << "x" << x << " count = " << ret.count << " --------------------XXX" << endl;
                    if (output)
                        cout << "Found a number: " << p << " count: " << ret.count << endl;
                }
            }
        }
        return ret;
    }

    //outf << "Level " << level << " started looping with pprev " << pprev << " and sprev " << sprev << " ----------vvvvv " << endl;
    for (int ai = aprev; ai <= k; ai++) {
        int count = ai > 1 ? countprev + 1 : countprev;
        int pact = pprev * ai;
        int sact = sprev + ai;
        int pfull_min = pact * int(pow(ai, l - level)); // provided all the rest elements are equal to ai too
        int sfull_min = sact + ai * (l - level);
        if (pfull_min == sfull_min) {
            count = l - level + 1;
            outf << "Level " << level << " found a product-sum number " << pfull_min << " = ... " << aprev << "x" << ai << " count = " << count << " --------------------XXX" << endl;
            if (output)
                cout << "Found a number: " << pfull_min << " count: " << count << endl;
            return result(true, pfull_min, count);
        }
        if (pfull_min > sfull_min) {
            //outf << "Level " << level << " returning due to p > s for ai " << ai << "; pfull = " << pfull_min << " sfull = " << sfull_min << " ----------^^^^^ " << endl;
            return ret;
        }
        //outf << "Level " << level << " making a recursive call for ai " << ai << "; pfull = " << pfull_min << " sfull = " << sfull_min << endl;
        result res = f(k, l, pact, sact, level, ai, count, output);
        if (res.found && res.number < ret.number) {
            ret = res;
        }
    }
    //outf << "Level " << level << " normal returning" << endl;
    return ret;
}

result solve_single(int k, bool output) {

    outf.open("test_single.dat");
    auto start = std::chrono::high_resolution_clock::now();

    if (k == 1) {
        return result(true, 1, 1);
    }
    else if (k == 2) {
        return result(true, 4, 2);
    }
    else if (k == 3) {
        return result(true, 6, 2);
    }

    // replace 1-s with 2-s
    int l = -1;
    int p = 1;
    int s = k;
    while (p <= s) {
        l++;
        p *= 2;
        s += 1;
    }

    result ret = f(k, l, 1, k - l, 0, 1, 0, output);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    if (output) {
        cout << "Minimal number        = " << ret.number << endl;
        cout << "Count of elements > 1 = " << ret.count << endl;
        cout << "Execution time        = " << t << " s" << endl;
    }
    outf.close();
    return ret;
}

void solve_multi(int k) {

    outf.open("test_multi.dat");

    auto start = std::chrono::high_resolution_clock::now();

    int num_max = 0;
    for (int ik = 2; ik <= k; ik++) {
        result res = solve_single(ik, false); // solve_single(ik);
        if (res.number > num_max) {
            num_max = res.number;
        }
        if (ik % 511 == 0)
            cout << ik << " : " << res.number << endl;
        outf << ik << " " << res.number << " " << res.count << endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Overall execution time    = " << t << " s" << endl;
    outf << "Overall execution time    = " << t << " s" << endl;

    outf.close();
}

int solve_sum(int k) {

    outf.open("test_sum.dat");

    auto start = std::chrono::high_resolution_clock::now();

    const int dim = 300000;
    int* mask = new int[dim];
    int num_max = 0;
    for (int ik = 2; ik <= k; ik++) {
        result res = solve_single(ik, false); // solve_single(ik);
        if (res.number > num_max) {
            num_max = res.number;
        }
        if (mask[res.number] == 0) {
            mask[res.number] = ik;
        }
        if (ik % 511 == 0)
            cout << ik << " : " << res.number << endl;
        outf << ik << " " << res.number << endl;
    }

    int sum = 0;
    for (int ik = 2; ik <= num_max; ik++) {
        if (mask[ik] > 0 && mask[ik] <= k)
            sum += ik;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Answer = " << sum << endl;
    cout << "Overall execution time    = " << t << " s" << endl;
    outf << "Answer = " << sum << endl;
    outf << "Overall execution time    = " << t << " s" << endl;

    outf.close();
    delete[] mask;
    return sum;
}

void fdiv_old(int n, int level, int p, int s, int dprev, int ndiv) {
    level++;
    int ndd = 0;
    int dend = int(sqrt(n));
    for (int d = dprev + 1; d <= dend; d++) {
        int nn = n; // result of the divisions
        int pp = p; // cumulative product
        int ss = s; // cumulative sum
        int nd = 0; // number of succesfull divisions by d
        while (nn % d == 0) {
            nd++;
            nn /= d;
            pp *= d;
            ss += d;

            // calculate k after each division
            if (nn > 1) {
                int ndivs = ndiv + nd + 1;
                int n1 = n - (ss + nn);
                int k = n1 + ndivs;
                cout << "--->Calculate k after the division by " << d << ": nd = " << ndivs << " p = " << n << " s = " << ss + nn << " k = " << k << endl;
                outf << "--->Calculate k after the division by " << d << ": nd = " << ndivs << " p = " << n << " s = " << ss + nn << " k = " << k << endl;
            }
        }
        ndd += nd;
        if (nd > 0) {
            // and recursive call
            cout << "Level " << level << ": " << n << " = " << d << "^" << nd << " x " << nn << " p = " << pp << " s = " << ss << endl;
            outf << "Level " << level << ": " << n << " = " << d << "^" << nd << " x " << nn << " p = " << pp << " s = " << ss << endl;
            fdiv_old(nn, level, pp, ss, d, ndiv + nd);
        }
    }
    // calculate k at the last level (if no divisions were done)
    if (ndd == 0) {
        p *= n;
        s += n;
        ndiv++;
        int n1 = p - s;
        int k = n1 + ndiv;
        cout << "--->Calculate k at the last level: nd =  " << ndiv << " p = " << p << " s = " << s << " k = " << k << endl;
        outf << "--->Calculate k at the last level: nd =  " << ndiv << " p = " << p << " s = " << s << " k = " << k << endl;
    }
}

void fdiv1(int n, int p, int level, string spc, int sum, int dprev, int* arr) {
    level++;
    spc.append(" ");
    for (int d = dprev; d * d <= p; d++) {
        ncallsall++;
        ncalls[level]++;
        if (p % d == 0) {
            int pp = p / d;
            int s = sum + d;
            arr[level - 1] = d;
            int k = n - (s + pp) + level + 1;
            if (n < nmin[k] || nmin[k] == 0)
                nmin[k] = n;
            if (k > kmax)
                kmax = k;
            if (k < kmin)
                kmin = k;
            //kset.insert(k);
            //cout << spc << "Level " << level << ": divisor = " << d << " partial sum = " << s << " full sum = " << s + p / d << " k = " << k << endl;
            //outf << spc << "Level " << level << ": divisor = " << d << " partial sum = " << s << " full sum = " << s + p / d << " k = " << k;
            arr[level] = p / d;
            //array_nonzero_print(outf, " divisors: ", arr, level + 1);
            arr[level] = 0;
            fdiv1(n, p / d, level, spc, s, d, arr);
            arr[level - 1] = 0;
        }
    }
}

void fdiv2(int n, int p, int level, string spc, int sum, int dprev, int* arr) {
    level++;
    spc.append(" ");
    cout << "Enter: level=" << level << " p = " << p << " sum = " << sum << endl;
    for (int d = dprev; d * d <= p; d++) {
        ncallsall++;
        ncalls[level]++;
        if (p % d == 0) {
            cout << spc << "level=" << level << " d = " << d << endl;
            fdiv2(n, p / d, level, spc, sum - d, d, arr);
        }
    }
}

void solve_fdiv1() {
    outf1.open("test_nmin.dat");
    outf2.open("test_kminmax.dat");
    auto start = std::chrono::high_resolution_clock::now();

    int n = 120;
    int* arr = new int[dim_div];
    //fdiv(n, 0, 1, 0, 1, 0);
    fdiv1(n, n, 0, "->", 0, 2, arr);
    //set_print(outf, "", kset);

    //n = 4;
    //while (true) {
    //    fdiv1(n, n, 0, "->", 0, 2, arr);
    //    outf2 << n << " " << kmin << " " << kmax << endl;
    //    if (kmin < 1000000 && kmin >= 12000)
    //        break;

    //    // next n
    //    kmin = 1000000;
    //    kmax = 0;
    //    n++;
    //}

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Overall execution time    = " << t << " s" << endl;
    cout << "Ncalls = " << ncallsall;
    array_nonzero_print(cout, " : ", ncalls, dim_div);
    array_nonzero_print2(outf1, "Nmin", nmin, dim_k);
    outf1 << "Overall execution time    = " << t << " s" << endl;
    outf1.close();
    outf2.close();
}

void solve_fdiv2() {
    outf.open("test_fdiv2.dat");
    //outf1.open("test_nmin.dat");
    //outf2.open("test_kminmax.dat");
    auto start = std::chrono::high_resolution_clock::now();

    int n = 120;
    int* arr = new int[dim_div];
    fdiv2(n, n, 0, "->", n, 2, arr);
    //set_print(outf, "", kset);

    //n = 4;
    //while (true) {
    //    fdiv1(n, n, 0, "->", 0, 2, arr);
    //    outf2 << n << " " << kmin << " " << kmax << endl;
    //    if (kmin < 1000000 && kmin >= 12000)
    //        break;

    //    // next n
    //    kmin = 1000000;
    //    kmax = 0;
    //    n++;
    //}

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Overall execution time    = " << t << " s" << endl;
    cout << "Ncalls = " << ncallsall;
    array_nonzero_print(cout, " : ", ncalls, dim_div);
    array_nonzero_print2(outf1, "Nmin", nmin, dim_k);
    outf1 << "Overall execution time    = " << t << " s" << endl;
    //outf1.close();
    //outf2.close();
    outf.close();
}

int main() {

    //int k = 12;
    //int res = solve_sum(k);
    //solve_multi(k);
    //result res = solve_single(k, true);
    solve_fdiv2();

    return 0;
}
