#include "Solution48.h"
#include "48.h"

void safe_mod_multiplication_test() {
    bool passed = true;

    ul n1 = 4836715601l;
    ul n2 = 2569995622l;
    ul res_exp = 9429098822l;
    ul res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 3415897173l;
    n2 = 5114489489l;
    res_exp = 6813314597l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 654654654656l;
    n2 = 54654354768l;
    res_exp = 1546999808l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 4294967296l;
    n2 = 2147483648l;
    res_exp = 6854775808l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 8642381783621l;
    n2 = 45111235899977l;
    res_exp = 2412876717l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 1l;
    n2 = 1l;
    res_exp = 1l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 1l;
    n2 = 2l;
    res_exp = 2l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 2l;
    n2 = 2l;
    res_exp = 4l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n1 = 11l;
    n2 = 22l;
    res_exp = 242l;
    res = safe_mod_multiplication(n1, n2);
    if (res != res_exp) {
        cout << n1 << " * " << n2 << " = " << res_exp << " actual = " << res << " failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    if (passed) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed!" << endl;
    }
}

void safe_mod_square_test() {
    bool passed = true;

    ul n = 1l;
    ul res_exp = 1l;
    ul res = safe_mod_square(n);
    if (res != res_exp) {
        cout << "Expected " << n << "^2 = " << res_exp << " whereas the actual result is = " << res << ": test failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n = 2l;
    res_exp = 4l;
    res = safe_mod_square(n);
    if (res != res_exp) {
        cout << "Expected " << n << "^2 = " << res_exp << " whereas the actual result is = " << res << ": test failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n = 5l;
    res_exp = 25l;
    res = safe_mod_square(n);
    if (res != res_exp) {
        cout << "Expected " << n << "^2 = " << res_exp << " whereas the actual result is = " << res << ": test failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n = 4836715601l;
    res_exp = 4956791201l;
    res = safe_mod_square(n);
    if (res != res_exp) {
        cout << "Expected " << n << "^2 = " << res_exp << " whereas the actual result is = " << res << ": test failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    n = 9415897173l;
    res_exp = 2509391929l;
    res = safe_mod_square(n);
    if (res != res_exp) {
        cout << "Expected " << n << "^2 = " << res_exp << " whereas the actual result is = " << res << ": test failed!" << endl;
        passed = false;
    }
    else {
        //cout << n1 << " * " << n2 << " = " << res << " passed!" << endl;
    }

    if (passed) {
        cout << "Passed!" << endl;
    }
    else {
        cout << "Failed!" << endl;
    }
}

void solve(ul N) {
    ul s = 0;
    for (ul a = 1l; a <= N; a++) {
        ul c = mod_binpow(a, a);
        s = (s + c) % tol;
    }
    cout << s << endl;
}

void test_one() {
    ul a = 1999993l;
    ul b = 1999993l;
    ul c1 = mod_power(a, b, tol);
    cout << "c1 = " << c1 << endl;
    ul c2 = mod_binpow(a, b);
    cout << "c2 = " << c2 << endl;

    if (c1 != c2) {
        cout << " Failed!!!" << endl;
    }
    else {
        cout << " Passed!!!" << endl;
    }
}

//ul partsum(ul t, ul n, ul m) {
//
//    // x(t) = t^t; q(t) = 2^t;
//    // x(2t) = (2t)^2t = q(2t)*x(t)^2; q(2t) = q(t)^2; etc.
//
//    ul sum = 0;
//
//    ul i = t; // indexes = t,2t,4t,...
//    ul q = mod_binpow(2l, t); // q(t) = 2^t
//    ul xt = mod_binpow(t, t); // x(t) = t^t
//    memo[i] = xt; // memoize
//    marked[i] = true;
//    sum = (sum + xt) % m;
//
//    while (true) {
//        i *= 2l;
//        if (i > n) {
//            break;
//        }
//        if (marked[i]) {
//            cout << "Repeat" << endl;
//        }
//        q = safe_mod_multiplication_rec(q, q, m); // q(2t) = q(t)^2
//        xt = safe_mod_multiplication_rec(xt, xt, m); // tmp = x(t)^2
//        xt = safe_mod_multiplication_rec(q, xt, m); // x(2t) = q(2t)*tmp
//        memo[i] = xt;
//        marked[i] = true;
//        sum = (sum + xt) % m;
//    }
//    return sum;
//}

int main() {

    ul n = 1999991;

    solve_brumme(n);

    outf.open("Euler48.out");

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    //getprimes();

    //solveBF(10000);

    solve(n);

    //test_one();
    //safe_mod_multiplication_test();
    //safe_mod_square_test();

    // all primes 1,2,3,5,...
    //ul sum = 0;
    //for (ul t = 1; t <= n; t++) {
    //    if (!marked[t]) {
    //        sum = (sum + partsum(t, n, tol)) % tol;
    //    }
    //}
    //cout << "Sum = " << sum << endl;
    //cout << "Ncalls small = " << ncalls1 << endl;
    //cout << "Ncalls big   = " << ncalls2 << endl;
    //cout << "Ncalls 3     = " << ncalls3 << endl;
    outf.close();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double time = duration.count() / 1E6;
    cout << "Execution time    = " << time << " s" << endl;
    return 0;
}
