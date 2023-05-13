#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <set>
#include <string>

using namespace std;

typedef long long int li;
typedef unsigned long long int lu;
typedef size_t sz;

const lu primelim = 10000000;
bool isprime[primelim + 1];
sz primes[primelim + 1];
sz nprimes;
lu s[primelim + 1];

struct four {
    int i1;
    int i2;
    int i3;
    lu i4;
    four(int i1, int i2, int i3, lu i4) {
        this->i1 = i1;
        this->i2 = i2;
        this->i3 = i3;
        this->i4 = i4;
    }
};

bool isaprime(lu n) {

    // Stored in the array
    if (n <= primelim)
    {
        return isprime[n];
    }

    //cout << "Passed to bigger values" << endl;

    // Re-calculate
    if (n == 2 || n == 3) {
        return true;
    }

    if (n <= 1 || n % 2 == 0 || n % 3 == 0) {
        return false;
    }

    for (lu i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}

void getprimes() {
    for (sz i = 2; i <= primelim; i++) {
        isprime[i] = true;
    }
    for (sz i = 2; i <= primelim; i++) {
        if (isprime[i]) {
            sz jst = i * i;
            for (sz j = jst; j <= primelim; j += i) {
                isprime[j] = false;
            }
        }
    }
    sz ipr = 0;
    for (sz i = 2; i <= primelim; i++) {
        if (isprime[i]) {
            primes[ipr++] = i;
        }
    }
    nprimes = ipr;
}

four getinitialsum(int ind, lu n) {
    int length = 0;
    lu stmp = 0;
    lu sres = 0;
    int i = ind;
    for (; i < nprimes; i++) {
        stmp += primes[i];
        if (stmp <= n) {
            s[i] = stmp;
            length++;
        }
        else {
            i--;
            //cout << "Last prime: P(" << i << ") = " << primes[i] << endl;
            break;
        }
    }
    int j = i;
    for (; j >= 0; j--) {
        if (isaprime(s[j])) {
            //cout << "S[" << j << "] = " << s[j] << endl;
            sres = s[j];
            break;
        }
        length--;
    }
    return four(ind, j, length, sres);
}

four trytoinsreasesum(int ilastini, int lengthini, lu n) {
    int is = ilastini;
    int lengthmax = lengthini;
    int indmax = 0;
    int imax = 0;
    lu smax = 0L;
    for (int ind = 1; ind < 100; ind++) {

        int i = is; // current start point is

        // minus the starting prime
        s[i] -= primes[ind - 1];

        // add the next primes
        lu stmp = s[i++];
        for (; i < nprimes; i++) {
            stmp += primes[i];
            if (stmp <= n) {
                s[i] = stmp;
            }
            else {
                i--;
                break;
            }
        }

        // now go back to find furthest prime
        // it makes no sense to go beyond the start index is
        // as we don't subtract the first primes 
        // from the sums with indexes less than the is
        bool found = false;
        for (; i > is; i--) {
            if (isaprime(s[i])) {
                found = true; // new prime sequential sum is found!
                is = i; // this will be the next start point
                break;
            }
        }
        if (found) {
            int length = i - ind + 1;
            if (length > lengthmax) {
                cout <<
                    " --> optimization: ind = " << ind <<
                    " i = " << i <<
                    " P(i) = " << primes[i] <<
                    " S[i] = " << s[i] <<
                    " length = " << length << endl;
                lengthmax = length;
                imax = i;
                indmax = ind;
                smax = s[i];
            }
            else if (lengthmax - length > 1000) {
                break;
            }
        }
    }
    return four(indmax, imax, lengthmax, smax);
}

void solve(lu n) {

    // Get primes
    getprimes();

    // Get the sequential sums
    int ind = 3;
    four res = getinitialsum(ind, n);

    // Output
    cout << "Initial length: ind = " << ind << " imax = " << res.i2 << " length = " << res.i3 << " sum = " << res.i4 << endl;
    four resnew = trytoinsreasesum(res.i1, res.i2, n);
    if (resnew.i1 > ind) {
        cout << "Maximum length: ind = " << resnew.i1 << " imax = " << resnew.i2 << " length = " << resnew.i3 << " sum = " << resnew.i4 << endl;
    }
}

int main() {

    const lu n = 1000000000000L;

    auto start = std::chrono::high_resolution_clock::now();
    //
    solve(n);
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
