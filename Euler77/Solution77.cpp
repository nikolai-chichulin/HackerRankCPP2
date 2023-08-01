#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

typedef signed long long int li;

const int nprimes = 1300;
const int maxprime = 10000;

li primes[nprimes];
bool isprime[maxprime];

li comb[1000][1000];

void zerocomb() {
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 1000; j++) {
            comb[i][j] = -1;
        }
    }
}

void getprimes() {
    for (li i = 2; i < maxprime; i++) {
        isprime[i] = true;
    }
    for (li i = 2; i < maxprime; i++) {
        if (isprime[i]) {
            li jst = i * i;
            for (li j = jst; j < maxprime; j += i) {
                isprime[j] = false;
            }
        }
    }
    int iprime = 0;
    for (int i = 0; i < maxprime; i++) {
        if (isprime[i]) {
            primes[iprime++] = i;
        }
    }
}

li getcomb(li n, li pmin) {

    if (comb[n][pmin] != -1) {
        return comb[n][pmin];
    }

    li ret = 0;
    if (n == 2 || n == 3) {
        if (pmin <= n) {
            ret = 1; // the only combination is n = n
        }
    }
    else if (n == 4) {
        if (pmin <= 2) {
            ret = 1; // the only combination is 4 = 2 + 2
        }
    }
    else if (n == 5) {
        if (pmin <= 2) {
            ret = 2; // the combinations are 1) 5 = 2 + 3 and 2) 5 = 5
        }
        else if (pmin <= 5) {
            ret = 1; // the only combination is 5 = 5
        }
    }
    else { // all other numbers are calculated with recursion

        // n = p + (n-p), p = 2,3,...,n/2
        for (li p = pmin; p <= n / 2; p++) {
            if (isprime[p]) {
                ret += getcomb(n - p, p);
            }
            //if (n == 12) {
            //    cout << " p = " << p << "  ret = " << ret << endl;
            //}
        }

        // add the equation n = n
        if (isprime[n]) {
            ret++;
        }
    }

    comb[n][pmin] = ret;
    return ret;
}

li getcomb2(li n, li ipmin) {

    li ret = 0;
    if (n == primes[ipmin]) {
        ret = 1; // only obvious combination n = n
    }
    else if (n == 2 || n == 3) {
        if (primes[ipmin] <= n) {
            ret = 1; // the only combination is n = n
        }
    }
    else if (n == 4) {
        if (primes[ipmin] <= 2) {
            ret = 1; // the only combination is 4 = 2 + 2
        }
    }
    else if (n == 5) {
        if (primes[ipmin] <= 2) {
            ret = 2; // the combinations are 1) 5 = 2 + 3 and 2) 5 = 5
        }
        else if (primes[ipmin] <= 5) {
            ret = 1; // the only combination is 5 = 5
        }
    }
    else if (primes[ipmin + 1] <= n) {
        ret = getcomb2(n - primes[ipmin], ipmin) + getcomb2(n, ipmin + 1);
    }
    return ret;
}

li solveBF1(li n) {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    //auto start = std::chrono::high_resolution_clock::now();

    getprimes();
    li ipmin = 0;
    li res1 = getcomb(n, primes[ipmin]);
    cout << "M1(" << n << "," << primes[ipmin] << ") = " << res1 << endl;

    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //double t = duration.count() / 1E6;
    //cout << "Execution time    = " << t << " s" << endl;

    return res1;
}

li solveBF2(li n) {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    getprimes();
    li ipmin = 0;
    li res2 = getcomb2(n, ipmin);
    cout << "M2(" << n << "," << primes[ipmin] << ") = " << res2 << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return res2;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    zerocomb();

    for (li n = 2; n <= 100; n++) {
        li res1 = solveBF1(n);
        //li res2 = solveBF2(n);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
