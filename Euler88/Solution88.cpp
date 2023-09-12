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

// PSN stands for product-sum number

ofstream outf;
ofstream outf1, outf2;

const int pmax = numeric_limits<int>::max();
const int dim = 210000; // maximal dimension of the problem
const int dim_div = 50; // maximal number of the factors

bool isprime[dim] = {};

//set<int> kset;
int nmin[dim] = {}; // nmin[k] is the minimal n for the given k; initially zeroes
bool nconsumed[dim] = {}; // nconsumed[n] = true if n has already been used in the sum; initially false

int ncalls[dim_div] = {}; // for debug: number of the funclion calls at the i-th depth
int ncallsall = 0; // for debug: overall number of the funclion calls

int kfound = 0; // number of k-s for which the minimal PSN have been found; finally it should be equal to kmax - 1
int finalsum = 0; // the final sum of PSN

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

void getprimes() {
    for (int i = 2; i < dim; i++) {
        isprime[i] = true;
    }
    for (int i = 2; i < dim; i++) {
        if (isprime[i]) {
            int jst = i * i;
            if (jst < dim) {
                for (int j = jst; j < dim; j += i) {
                    isprime[j] = false;
                }
            }
            else {
                break;
            }
        }
    }
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

result solve_single_old(int k, bool output) {

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
        result res = solve_single_old(ik, false); // solve_single(ik);
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

int solve_sum_old(int k) {

    outf.open("test_sum.dat");

    auto start = std::chrono::high_resolution_clock::now();

    const int dim = 300000;
    int* mask = new int[dim];
    int num_max = 0;
    for (int ik = 2; ik <= k; ik++) {
        result res = solve_single_old(ik, false); // solve_single(ik);
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

void fdiv(int n, int kend, int p, int level, int sum, int dprev, int* factors) {
    level++;
    int dend = int(sqrt(p));
    for (int d = dprev; d <= dend; d++) {
        //ncallsall++;
        //ncalls[level]++;
        if (p % d == 0) {
            int pp = p / d;
            int s = sum + d;
            //factors[level - 1] = d;
            int k = n - (s + pp) + level + 1;
            if (k <= kend) {
                if (nmin[k] == 0 || n < nmin[k]) {
                    kfound++; // number of the k-s for which n is the minimal PSN
                    nmin[k] = n;
                    if (!nconsumed[n]) { // if the n hasn not been already counted, count it
                        finalsum += n;
                        nconsumed[n] = true;
                    }
                }
            }
            //kset.insert(k);
            //cout << spc << "Level " << level << ": divisor = " << d << " partial sum = " << s << " full sum = " << s + p / d << " k = " << k;
            //outf1 << spc << "Level " << level << ": divisor = " << d << " partial sum = " << s << " full sum = " << s + p / d << " k = " << k;
            //factors[level] = p / d;
            //array_nonzero_print(cout, " divisors: ", factors, level + 1);
            //factors[level] = 0;
            fdiv(n, kend, pp, level, s, d, factors);
            //factors[level - 1] = 0;
        }
    }
}

void fdiv_opt(int n, int kend, int p, int level, int sum, int dprev) {
    level++;
    int kconst = n - sum + level + 1;
    int dend = int(sqrt(p));
    for (int d = dprev; d <= dend; d++) {
        if (p % d == 0) {
            int pp = p / d;
            int k = kconst - d - pp; // n - (s + pp) + level + 1;
            if (k <= kend) {
                if (nmin[k] == 0 || n < nmin[k]) {
                    kfound++; // number of the k-s for which n is the minimal PSN
                    nmin[k] = n;
                    if (!nconsumed[n]) { // if the n hasn not been already counted, count it
                        finalsum += n;
                        nconsumed[n] = true;
                    }
                }
            }
            fdiv_opt(n, kend, pp, level, sum + d, d);
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

void solve_single(int n) {
    outf1.open("test_nmin.dat");
    //outf2.open("test_kminmax.dat");
    auto start = std::chrono::high_resolution_clock::now();

    int kmax = 200000;
    int* factors = new int[dim_div];
    fdiv(n, kmax, n, 0, 0, 2, factors);
    //set_print(outf, "", kset);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Overall execution time    = " << t << " s" << endl;
    //cout << "Ncalls = " << ncallsall;
    //array_nonzero_print(cout, " : ", ncalls, dim_div);
    array_nonzero_print2(outf1, "Nmin", nmin, dim);
    outf1 << "Overall execution time    = " << t << " s" << endl;
    outf1.close();
    //outf2.close();
}

void solve_sum(int kmax) {
    outf1.open("test_nmin.dat");
    //outf2.open("test_kminmax.dat");
    auto start = std::chrono::high_resolution_clock::now();

    getprimes();

    int* factors = new int[dim_div];
    int n = 4;
    while (true) {
        if (!isprime[n]) {
            //fdiv(n, kmax, n, 0, 0, 2, factors);
            fdiv_opt(n, kmax, n, 0, 0, 2);
        }
        //outf2 << n << " " << kmin << " " << kmax << endl;
        if (kfound == kmax - 1) {
            break;
        }

        n++;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Overall execution time    = " << t << " s" << endl;
    cout << "Final sum = " << finalsum << endl;
    cout << "Ncalls = " << ncallsall;
    array_nonzero_print(cout, " : ", ncalls, dim_div);
    array_nonzero_print2(outf1, "Nmin", nmin, dim);
    outf1 << "Overall execution time    = " << t << " s" << endl;
    outf1.close();
    //outf2.close();
}

void solve_opt(int kmax) {
    auto start = std::chrono::high_resolution_clock::now();

    getprimes();

    int n = 4;
    while (true) {
        if (!isprime[n]) {
            fdiv_opt(n, kmax, n, 0, 0, 2);
        }
        if (kfound == kmax - 1) {
            break;
        }

        n++;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Overall execution time    = " << t << " s" << endl;
    cout << "Final sum = " << finalsum << endl;
}

int main() {

    //solve_single(200000);
    //solve_sum(200000);
    solve_opt(12);

    return 0;
}
