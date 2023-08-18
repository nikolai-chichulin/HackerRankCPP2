#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

using namespace std;

typedef signed long long int li;

const int nprimes = 18000;
const int maxprime = 200000;

li primes[nprimes];
bool isprime[maxprime];
vector<li> divisors[maxprime];

const li limfact = 20000;
li factors[limfact]; // prime factors

ofstream outf1, outf2, outf3;
li resa[500000];
li powers[10][30]; // powers
li mult[21][14][11][9][9][8][7][7]; // multiplications a2/a3.../a9
li sums[21][14][11][9][9][8][7][7]; // sums a2/a3.../a9

li imult = 0;
li isumm = 0;

//
const li n2 = 21;
const li n3 = 14;
const li n4 = 11;
const li n56 = 9;
const li n7 = 8;
const li n89 = 7;

//
li sum2[n2] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
li sum3[n3] = { 0,3,6,9,12,15,18,21,24,27,30,33,36,39 };
li sum4[n4] = { 0,4,8,12,16,20,24,28,32,36,40 };
li sum5[n56] = { 0,5,10,15,20,25,30,35,40 };
li sum6[n56] = { 0,6,12,18,24,30,36,42,48 };
li sum7[n7] = { 0,7,14,21,28,35,42,49 };
li sum8[n89] = { 0,8,16,24,32,40,48 };
li sum9[n89] = { 0,9,18,27,36,45,54 };

//
li mult2[n2] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576 };
li mult3[n3] = { 1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323 };
li mult4[n4] = { 1,4,16,64,256,1024,4096,16384,65536,262144,1048576 };
li mult5[n56] = { 1,5,25,125,625,3125,15625,78125,390625 };
li mult6[n56] = { 1,6,36,216,1296,7776,46656,279936,1679616 };
li mult7[n7] = { 1,7,49,343,2401,16807,117649,823543 };
li mult8[n89] = { 1,8,64,512,4096,32768,262144 };
li mult9[n89] = { 1,9,81,729,6561,59049,531441 };

//--------------------------------------------------------------

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

void getprimes2() {
    for (li i = 2; i < maxprime; i++) {
        isprime[i] = true;
    }
    for (li i = 2; i < maxprime; i++) {
        if (isprime[i]) {
            li jst = i * i;
            for (li j = jst; j < maxprime; j += i) {
                isprime[j] = false;
                divisors[j].push_back(i);
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

// Prime factorizations of the given number
bool primetest(li p) {

    li nfact = 0;
    li iprime = 0;
    bool ret = false;
    if (p == 2) {
        ret = true;
        factors[nfact++] = 2;
    }
    else if (p == 3) {
        ret = true;
        factors[nfact++] = 3;
    }
    else if (p > 1) {
        li ptmp = p;
        for (iprime = 0; iprime < nprimes; iprime++) { // loop for small primes (<= sqrt(p))
            li prime = primes[iprime];
            if (prime * prime > p) {
                break;
            }
            while (ptmp % prime == 0)
            {
                ptmp /= prime;
                factors[nfact++] = prime;
            }
        }
        if (nfact == 0) { // if no small primes - this is a prime, add the number itself
            ret = true;
            factors[nfact++] = ptmp;
        }
        else if (ptmp != 1) {
            factors[nfact++] = ptmp;
        }
    }

    if (ret)
    {
        //outf << "P(" << ind << ")=" << p << " - prime; depth - " << iprime << endl;
    }
    else {
        //outf << "P(" << ind << ")=" << p << " - composite; depth - " << iprime << endl;
    }

    return ret;
}

li getsum(li a1, li a2, li a3, li a4, li a5, li a6, li a7, li a8, li a9) {
    return a1 + a2 * 2l + a3 * 3l + a4 * 4l + a5 * 5l + a6 * 6l + a7 * 7l + a8 * 8l + a9 * 9l;
}

li powint(li b, li e) {
    imult++;
    if (powers[b][e] == 0) {
        powers[b][e] = 1;
        for (li i = 0; i < e; i++) {
            powers[b][e] *= b;
        }
    }
    return powers[b][e];
}

li getmult(li a1, li a2, li a3, li a4, li a5, li a6, li a7, li a8, li a9) {
    li p2 = powint(2, a2);
    li p3 = powint(3, a3);
    li p4 = powint(4, a4);
    li p5 = powint(5, a5);
    li p6 = powint(6, a6);
    li p7 = powint(7, a7);
    li p8 = powint(8, a8);
    li p9 = powint(9, a9);
    return p2 * p3 * p4 * p5 * p6 * p7 * p8 * p9;
}

li getmultN(li a1, li a2, li a3, li a4, li a5, li a6, li a7, li a8, li a9) {
    if (mult[a2][a3][a4][a5][a6][a7][a8][a9] == 0) {
        li p2 = powint(2, a2);
        li p3 = powint(3, a3);
        li p4 = powint(4, a4);
        li p5 = powint(5, a5);
        li p6 = powint(6, a6);
        li p7 = powint(7, a7);
        li p8 = powint(8, a8);
        li p9 = powint(9, a9);
        mult[a2][a3][a4][a5][a6][a7][a8][a9] = p2 * p3 * p4 * p5 * p6 * p7 * p8 * p9;
    }
    return mult[a2][a3][a4][a5][a6][a7][a8][a9];
}

/// <summary>
/// Returns the product-sum number for the given k.
/// </summary>
/// <param name="k">k is the number of terms/multipliers</param>
/// <returns></returns>
li getres1(li k) {
    li smax = 9l * li(k); // theoretical maximal sum
    double smaxl = log10(smax);
    li a2max = li(smaxl / log10(2)); // maximal count of 2-s
    li ret = -1;
    bool zerooverflow = false;
    for (li a2 = 0; a2 <= a2max; a2++) { // the loop over the 2-s number
        //outf2 << "->a2=" << a2 << endl;
        // recalculate the theoretical maximum of the sum for a2 twos and k-a2 nines
        smax = getsum(0, a2, 0, 0, 0, 0, 0, 0, k - a2);
        smaxl = log10(smax);
        li a3max = li(smaxl / log10(3)); // maximal count of 3-s
        for (li a3 = 0; a3 <= a3max; a3++) { // the loop over the 3-s number
            //outf2 << "-->a3=" << a3 << endl;
            // recalculate the theoretical maximum of the sum for a2 twos, a3 threes, and k-a2 nines
            smax = getsum(0, a2, a3, 0, 0, 0, 0, 0, k - a2 - a3);
            smaxl = log10(smax);
            li a4max = li(smaxl / log10(4)); // maximal count of 4-s
            for (li a4 = 0; a4 <= a4max; a4++) { // the loop over the 4-s number
                //outf2 << "--->a4=" << a4 << endl;
                // recalculate the theoretical maximum of the sum...
                smax = getsum(0, a2, a3, a4, 0, 0, 0, 0, k - a2 - a3 - a4);
                smaxl = log10(smax);
                li a5max = li(smaxl / log10(5));
                for (li a5 = 0; a5 <= a5max; a5++) {
                    //outf2 << "---->a5=" << a5 << endl;
                    // recalculate the theoretical maximum of the sum...
                    smax = getsum(0, a2, a3, a4, a5, 0, 0, 0, k - a2 - a3 - a4 - a5);
                    smaxl = log10(smax);
                    li a6max = li(smaxl / log10(6));
                    for (li a6 = 0; a6 <= a6max; a6++) {
                        //outf2 << "----->a6=" << a6 << endl;
                        // recalculate the theoretical maximum of the sum...
                        smax = getsum(0, a2, a3, a4, a5, a6, 0, 0, k - a2 - a3 - a4 - a5 - a6);
                        smaxl = log10(smax);
                        li a7max = li(smaxl / log10(7));
                        for (li a7 = 0; a7 <= a7max; a7++) {
                            //outf2 << "------>a7=" << a7 << endl;
                            // recalculate the theoretical maximum of the sum...
                            smax = getsum(0, a2, a3, a4, a5, a6, a7, 0, k - a2 - a3 - a4 - a5 - a6 - a7);
                            smaxl = log10(smax);
                            li a8max = li(smaxl / log10(8));
                            for (li a8 = 0; a8 <= a8max; a8++) {
                                //outf2 << "------->a8=" << a8 << endl;
                                // recalculate the theoretical maximum of the sum...
                                smax = getsum(0, a2, a3, a4, a5, a6, a7, a8, k - a2 - a3 - a4 - a5 - a6 - a7 - a8);
                                smaxl = log10(smax);
                                li a9max = li(smaxl / log10(9));
                                for (li a9 = 0; a9 <= a9max; a9++) {
                                    //outf2 << "-------->a9=" << a9 << endl;
                                    li a1 = k - a2 - a3 - a4 - a5 - a6 - a7 - a8 - a9;
                                    li sum = getsum(a1, a2, a3, a4, a5, a6, a7, a8, a9);
                                    li mult = getmultN(a1, a2, a3, a4, a5, a6, a7, a8, a9);
                                    if (mult > sum) {
                                        zerooverflow = a9 == 0;
                                        if (zerooverflow) {
                                            //outf2 << " zero overflow a9, break " << endl;
                                        }
                                        else {
                                            //outf2 << " overflow a9, break " << endl;
                                        }
                                        break;
                                    }
                                    if (sum == mult) {
                                        outf1 << " found the number: " << sum << endl;
                                        outf2 << " k = " << k << " number = " << sum << " a: " << a1 << ", " << a2 << ", " << a3 << ", " << a4 << ", " << a5 << ", " << a6 << ", " << a7 << ", " << a8 << ", " << a9 << endl;
                                        if (ret == -1 || sum < ret) {
                                            ret = sum;
                                        }
                                        break;
                                    }
                                }
                                if (zerooverflow) {
                                    zerooverflow = a8 == 0;
                                    //if (zerooverflow) {
                                    //    outf2 << " zero overflow a8, break " << endl;
                                    //}
                                    //else {
                                    //    outf2 << " overflow a8, break " << endl;
                                    //}
                                    break;
                                }
                            }
                            if (zerooverflow) {
                                zerooverflow = a7 == 0;
                                //if (zerooverflow) {
                                //    outf2 << " zero overflow a7, break " << endl;
                                //}
                                //else {
                                //    outf2 << " overflow a7, break " << endl;
                                //}
                                break;
                            }
                        }
                        if (zerooverflow) {
                            zerooverflow = a6 == 0;
                            //if (zerooverflow) {
                            //    outf2 << " zero overflow a6, break " << endl;
                            //}
                            //else {
                            //    outf2 << " overflow a6, break " << endl;
                            //}
                            break;
                        }
                    }
                    if (zerooverflow) {
                        zerooverflow = a5 == 0;
                        //if (zerooverflow) {
                        //    outf2 << " zero overflow a5, break " << endl;
                        //}
                        //else {
                        //    outf2 << " overflow a5, break " << endl;
                        //}
                        break;
                    }
                }
                if (zerooverflow) {
                    zerooverflow = a4 == 0;
                    //if (zerooverflow) {
                    //    outf2 << " zero overflow a4, break " << endl;
                    //}
                    //else {
                    //    outf2 << " overflow a4, break " << endl;
                    //}
                    break;
                }
            }
            if (zerooverflow) {
                zerooverflow = a3 == 0;
                //if (zerooverflow) {
                //    outf2 << " zero overflow a3, break " << endl;
                //}
                //else {
                //    outf2 << " overflow a3, break " << endl;
                //}
                break;
            }
        }
        if (zerooverflow) {
            zerooverflow = a2 == 0;
            //if (zerooverflow) {
            //    outf2 << " zero overflow a2, break " << endl;
            //}
            //else {
            //    outf2 << " overflow a2, break " << endl;
            //}
            break;
        }
    }
    if (ret != -1) {
        outf1 << "  ---> the final sum is: " << ret << endl;
    }
    return ret;
}

void solve() {
    li kmax = 0;
    li nfactmax = 0;
    for (li n = 2; n <= 200000; n++) {
        if (isprime[n]) { // ignore prime numbers
            continue;
        }
        // factorize the number as short as possible
        outf3 << " factorization " << n << " = ";
        li nfact = 0;
        li ntmp = n;
        li s = 0;
        for (li div : divisors[n]) {
            while (ntmp % div == 0) {
                ntmp /= div;
                s += div;
                nfact++;
                outf3 << div << " ";
            }
        }
        if (ntmp != 1) {
            s += ntmp;
            nfact++;
            outf3 << ntmp << " ";
        }
        outf3 << " nfact = " << nfact;
        outf3 << " sum = " << s;
        li n1 = n - s;
        outf3 << " n1 = " << n1;
        li k = nfact + n1;
        outf3 << " k = " << k << endl;
        if (k > kmax) {
            kmax = k;
        }
        if (nfact > nfactmax) {
            nfactmax = nfact;
        }
        //for (li i = 2; i <= n / 2; i++) {
        //    if (n % i == 0) {
        //        // n = i * (n/i)
        //        li s = i + n / i;
        //        li n1 = n - s;
        //        li k = 2 + n1;
        //        if (k > kmax) {
        //            kmax = k;
        //        }
        //        //if (n % 1000 == 0)
        //        outf3 << n << " = " << i << " * " << n / i << " k = " << k << " kmax = " << kmax << endl;
        //    }
        //}
    }
    outf3 << " nfactmax = " << nfactmax << endl;
}

int main() {

    //outf1.open("test1.out");
    //outf2.open("test2.out");
    outf3.open("test3.out");

    auto start = std::chrono::high_resolution_clock::now();

    getprimes2();
    solve();

    //getpows(25);
    //li tmp = prerun();
    //cout << tmp << endl;

    //li resmax = 0;
    //li kmax = 1000;
    //for (li k = 2; k <= kmax; k++) {
    //    li resk1 = getres1(k);
    //    //li resk1 = getres3(k);
    //    //if (resk2 != resk1) {
    //    //    cout << "Alarm at: " << k << endl;
    //    //    cout << " Var 1 res = " << resk1 << endl;
    //    //    cout << " Var 2 res = " << resk2 << endl;
    //    //}
    //    if (resk1 > -1) {
    //        resa[resk1]++;
    //        if (k % 100 == 0)
    //            cout << "k = " << k << " res = " << resk1 << endl;
    //        outf1 << "k = " << k << " res = " << resk1 << endl;
    //    }
    //    if (resk1 > resmax) {
    //        resmax = resk1;
    //    }
    //}

    //li res = 0;
    //for (li i = 0; i <= resmax; i++) {
    //    if (resa[i] > 0) {
    //        res += i;
    //    }
    //}
    //cout << "The answer is = " << res << endl;
    //cout << "The maximal res is = " << resmax << endl;
    //cout << "isumm = " << isumm << " imult = " << imult << endl;
    //outf1 << "The answer is = " << res << endl;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    outf1 << "Execution time    = " << t << " s" << endl;

    //outf1.close();
    //outf2.close();
    outf3.close();

    return 0;
}
