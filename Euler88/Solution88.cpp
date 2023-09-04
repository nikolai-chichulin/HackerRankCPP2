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
ofstream outlevel[20];

const int pmax = numeric_limits<int>::max();
int ncalls = 0;

int f(int k, int l, int pprev, int sprev, int level, int aprev) {
    //ncalls++;
    level++;

    //outlevel[level] << "Level: " << level << " start looping with " << aprev << endl;

    int ret = pmax;

    if (level == l) {
        if (pprev > 1) {
            if (sprev % (pprev - 1) == 0) {
                int x = sprev / (pprev - 1);
                if (x >= aprev) {
                    int p = pprev * x;
                    cout << "Found a number:" << p << endl;
                    //outlevel[level] << "Found a number:" << p << endl;
                    ret = p;
                }
            }
        }
        return ret;
    }

    for (int ai = aprev; ai <= k; ai++) {
        int pact = pprev * ai;
        int sact = sprev + ai;
        int pfull_min = pact * int(pow(ai, l - level));
        int sfull_min = sact + ai * (l - level);
        //outlevel[level] << "Level: " << level << " new element: " << ai << endl;
        if (pfull_min == sfull_min) {
            return pfull_min;
        }
        if (pfull_min > sfull_min) {
            return ret;
        }
        //outf << "Not the last level: " << ai << endl;
        int res = f(k, l, pact, sact, level, ai);
        if (res < ret) {
            ret = res;
        }
    }
    return ret;
}

int solve_new(int k) {
    auto start = std::chrono::high_resolution_clock::now();

    //outf.open("test.dat");
    //outlevel[1].open("level1.dat");
    //outlevel[2].open("level2.dat");
    //outlevel[3].open("level3.dat");
    //outlevel[4].open("level4.dat");
    //outlevel[5].open("level5.dat");
    //outlevel[6].open("level6.dat");
    //outlevel[7].open("level7.dat");
    //outlevel[8].open("level8.dat");
    //outlevel[9].open("level9.dat");
    //outlevel[10].open("level10.dat");

    if (k == 1) {
        return 1;
    }
    else if (k == 2) {
        return 4;
    }
    else if (k == 3) {
        return 6;
    }

    int l = int(log10(k) / log10(2)) + 1;
    int ret = f(k, l, 1, k - l, 0, 1);

    //outf.close();
    //outlevel[1].close();
    //outlevel[2].close();
    //outlevel[3].close();
    //outlevel[4].close();
    //outlevel[5].close();
    //outlevel[6].close();
    //outlevel[7].close();
    //outlevel[8].close();
    //outlevel[9].close();
    //outlevel[10].close();

    //cout << "Ncalls = " << ncalls << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;

    cout << "Answer = " << ret << endl;
    cout << "Overall execution time    = " << t << " s" << endl;
    return ret;
}

int solve_sum(int k) {

    outf.open("test.dat");

    auto start = std::chrono::high_resolution_clock::now();

    const int dim = 300000;
    int* mask = new int[dim];
    int res_max = 0;
    for (int ik = 2; ik <= k; ik++) {
        int res = solve_new(ik); // solve_single(ik);
        if (res > res_max) {
            res_max = res;
        }
        if (mask[res] == 0) {
            mask[res] = ik;
        }
        if (ik % 511 == 0)
            cout << ik << " : " << res << endl;
        outf << ik << " " << res << endl;
    }

    int sum = 0;
    for (int ik = 2; ik <= res_max; ik++) {
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
    int res = solve_new(k);

    return 0;
}
