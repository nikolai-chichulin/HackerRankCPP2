#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <limits>

using namespace std;

ofstream outf;

const int pmax = numeric_limits<int>::max();

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
    bool found;
    int number;
    int count;
};

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
                    if (output)
                        cout << "Found a number: " << p << " count: " << ret.count << endl;
                }
            }
        }
        return ret;
    }

    for (int ai = aprev; ai <= k; ai++) {
        int count = ai > 1 ? countprev + 1 : countprev;
        int pact = pprev * ai;
        int sact = sprev + ai;
        int pfull_min = pact * int(pow(ai, l - level));
        int sfull_min = sact + ai * (l - level);
        if (pfull_min == sfull_min) {
            count = l - level + 1;
            if (output)
                cout << "Found a number: " << pfull_min << " count: " << count << endl;
            return result(true, pfull_min, count);
        }
        if (pfull_min > sfull_min) {
            return ret;
        }
        result res = f(k, l, pact, sact, level, ai, count, output);
        if (res.found && res.number < ret.number) {
            ret = res;
        }
    }
    return ret;
}

result solve_single(int k, bool output) {
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
    while (p < s) {
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

int main() {

    int k = 200000;
    //int res = solve_sum(k);
    solve_multi(k);
    //result res = solve_single(k, true);

    return 0;
}
