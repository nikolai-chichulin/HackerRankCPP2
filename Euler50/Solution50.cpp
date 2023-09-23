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

const lu dim = 1000000000000UL;
const lu primelim = 10000000UL;
bool isprime[primelim + 1];
sz primes[primelim + 1];
sz nprimes;
lu s[primelim + 1];

/// <summary>
/// Returns i: a[i]<=target<=arr[i+1] given that the array is ascending order.
/// </summary>
/// <param name="data">The array.</param>
/// <param name="start">Start index (inclusive).</param>
/// <param name="end">End index (exclusive).</param>
/// <param name="target">A number to search for.</param>
/// <param name="is">Optional: starting index.</param>
/// <param name="addition">Optional: a term to add to each element.</param>
/// <returns></returns>
int binary_search(const lu* data, int start, int end, lu target, int is = 0, lu addition = 0) {

    if (target >= (data[end - 1] - addition)) {
        return end - 1;
    }
    if (target < (data[start] - addition)) {
        return -1;
    }
    if (target == (data[start] - addition)) {
        return start;
    }
    if ((data[is] - addition) <= target && target <= (data[is + 1] - addition)) {
        return is;
    }

    int il = start;
    int ir = end - 1;
    is = (il + ir) / 2;
    while (true) {
        if ((data[is] - addition) <= target && target <= (data[is + 1] - addition)) {
            return int(is);
        }
        if (target > (data[is] - addition)) {
            il = is;
        }
        else {
            ir = is;
        }
        is = (il + ir) / 2;
    }
    return -1;
}

bool isaprime(lu n) {

    // Stored in the array
    if (n <= primelim)
    {
        return isprime[n];
    }

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

int getsums() {
    int length = 0;
    lu stmp = 0;
    int last_prime = 0;
    for (int i = 1; i <= nprimes; i++) {
        stmp += primes[i - 1];
        if (stmp <= dim) {
            length++;
            s[i] = stmp;
            last_prime = i - 1;
        }
        else {
            break;
        }
    }
    //cout << "Getsums: length           = " << length << endl;
    //cout << "Getsums: the last prime   = " << primes[last_prime] << endl;
    //cout << "Getsums: the last sum     = " << s[length] << endl;
    //cout << "Getsums: the gap to 10^12 = " << dim - s[length] << endl;
    //cout << "Getsums: the next prime   = " << primes[last_prime + 1] << " makes the sums > N" << endl;
    return length;
}

void solve(int length, lu n, lu prime_exp, int length_exp) {

    // Get index of the rightmost sum <= n
    int pos_right = binary_search(s, 1, length + 1, n);

    // Given the index of the first prime to sum is pos_left,
    // calculate the first prime of the sums starting from the pos_right
    int max_length = 0;
    lu res_prime = 0;
    int res_pos_left = 0;
    for (int pos_left = 0; pos_left < 20; pos_left++) {
        int length_tmp = 0;
        lu prime_tmp = 0;

        // correct pos_right if needed, because the sums are getting smaller
        if (pos_left > 0)
            pos_right = binary_search(s, pos_left + 1, length + 1, n, pos_right, s[pos_left]);

        // scan the array to search for the first prime
        for (int i = pos_right; i > pos_left; i--) {
            lu sum_reduced = s[i] - s[pos_left];
            if (isaprime(sum_reduced)) {
                //cout << "i = " << i << endl;
                length_tmp = i - pos_left;
                prime_tmp = sum_reduced;
                if (length_tmp > max_length) {
                    max_length = length_tmp;
                    res_prime = sum_reduced;
                    res_pos_left = pos_left;
                }
                break;
            }
        }
        //cout << "N = " << n << " Prime " << prime_tmp << " is a sum of " << length_tmp << " primes starting from " << primes[pos_left] << endl;
    }
    //cout << "Final result for N = " << n << ": prime " << res_prime << " is a sum of " << max_length << " primes starting from " << primes[res_pos_left] << endl;
    if (res_prime == prime_exp && max_length == length_exp) {
        cout << "N = " << n << " passed!" << endl;
    }
    else {
        cout << "N = " << n << " failed!" << endl;
        cout << "prime act  = " << res_prime << " prime exp = " << prime_exp << endl;
        cout << "length act = " << max_length << " length exp = " << length_exp << endl;
    }
}

void solve_debug() {
    // Get primes
    getprimes();

    // Get the sequential sums and their length
    int length = getsums();

    lu n = 2UL;
    solve(length, n, 2UL, 1);
}

void solve() {
    // Get primes
    getprimes();

    // Get the sequential sums and their length
    int length = getsums();

    lu n = 2UL;
    solve(length, n, 2UL, 1);
    n = 3UL;
    solve(length, n, 2UL, 1);
    n = 100UL;
    solve(length, n, 41UL, 6);
    n = 1000UL;
    solve(length, n, 953UL, 21);
    n = 2000000UL;
    solve(length, n, 1999219UL, 749);
    n = 1783562573UL;
    solve(length, n, 1782822889UL, 18345);
    n = 2000000001UL;
    solve(length, n, 1999021753UL, 19371);
    n = 4000000001UL;
    solve(length, n, 3999458657UL, 26939);
    n = 5000000001UL;
    solve(length, n, 4999713847UL, 29961);
    n = 6000000001UL;
    solve(length, n, 5999600857UL, 32687);
    n = 7000000001UL;
    solve(length, n, 6998090059UL, 35177);
    n = 20000000001UL;
    solve(length, n, 19999691651UL, 58073);
    n = 84754975923UL;
    solve(length, n, 84752639107UL, 115926);
    n = 984754975923UL;
    solve(length, n, 984747421873UL, 376525);
    n = 500000000000UL;
    solve(length, n, 499964183321UL, 271764);
    n = 978787887777UL;
    solve(length, n, 978785118401UL, 375423);
    n = 999999999999UL;
    solve(length, n, 999973156643UL, 379317);
    n = 1000000000000UL;
    solve(length, n, 999973156643UL, 379317);
}

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    //
    solve();
    //
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
