#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;
typedef long long int li;

bool condition5(li a, li b, li c) {
    return (a + b + c) % 3 == 0;
}

bool condition7(li a, li b, li c) {
    return (100 * a + 10 * b + c) % 7 == 0;
}

bool condition8(li a, li b, li c) {
    return (100 * a + 10 * b + c) % 11 == 0;
}

bool condition9(li a, li b, li c) {
    return (100 * a + 10 * b + c) % 13 == 0;
}

bool condition10(li a, li b, li c) {
    return (100 * a + 10 * b + c) % 17 == 0;
}

void solve9() { // n=9: 10 digits from 0 to 9
    const li i4a[] = { 0,2l,4l,6l,8l };
    const li i6a[] = { 0,5l };
    li n = 9;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        for (li i6 : i6a) {
                            if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1)
                                continue;
                            for (li i7 = 0; i7 <= n; i7++) {
                                if (i7 == i6 || i7 == i5 || i7 == i4 || i7 == i3 || i7 == i2 || i7 == i1 || !condition7(i5, i6, i7))
                                    continue;
                                for (li i8 = 0; i8 <= n; i8++) {
                                    if (i8 == i7 || i8 == i6 || i8 == i5 || i8 == i4 || i8 == i3 || i8 == i2 || i8 == i1 || !condition8(i6, i7, i8))
                                        continue;
                                    for (li i9 = 0; i9 <= n; i9++) {
                                        if (i9 == i8 || i9 == i7 || i9 == i6 || i9 == i5 || i9 == i4 || i9 == i3 || i9 == i2 || i9 == i1 || !condition9(i7, i8, i9))
                                            continue;
                                        for (li i10 = 0; i10 <= n; i10++) {
                                            if (i10 == i9 || i10 == i8 || i10 == i7 || i10 == i6 || i10 == i5 || i10 == i4 || i10 == i3 || i10 == i2 || i10 == i1 || !condition10(i8, i9, i10))
                                                continue;
                                            // cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9 << i10 << endl;
                                            nn++;
                                            li add = li(1000000000l * i1)
                                                + li(100000000l * i2)
                                                + li(10000000l * i3)
                                                + li(1000000l * i4)
                                                + li(100000l * i5)
                                                + li(10000l * i6)
                                                + li(1000l * i7)
                                                + li(100l * i8)
                                                + li(10l * i9)
                                                + li(i10);
                                            sum = sum + add;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve8() { // n=8: 9 digits from 0 to 8
    const li i4a[] = { 0,2l,4l,6l,8l };
    const li i6a[] = { 0,5l };
    li n = 8;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        for (li i6 : i6a) {
                            if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1)
                                continue;
                            for (li i7 = 0; i7 <= n; i7++) {
                                if (i7 == i6 || i7 == i5 || i7 == i4 || i7 == i3 || i7 == i2 || i7 == i1 || !condition7(i5, i6, i7))
                                    continue;
                                for (li i8 = 0; i8 <= n; i8++) {
                                    if (i8 == i7 || i8 == i6 || i8 == i5 || i8 == i4 || i8 == i3 || i8 == i2 || i8 == i1 || !condition8(i6, i7, i8))
                                        continue;
                                    for (li i9 = 0; i9 <= n; i9++) {
                                        if (i9 == i8 || i9 == i7 || i9 == i6 || i9 == i5 || i9 == i4 || i9 == i3 || i9 == i2 || i9 == i1 || !condition9(i7, i8, i9))
                                            continue;
                                        // cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << i9 << endl;
                                        nn++;
                                        li add = li(100000000l * i1)
                                            + li(10000000l * i2)
                                            + li(1000000l * i3)
                                            + li(100000l * i4)
                                            + li(10000l * i5)
                                            + li(1000l * i6)
                                            + li(100l * i7)
                                            + li(10l * i8)
                                            + li(i9);
                                        sum = sum + add;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve7() { // n=7: 8 digits from 0 to 7
    const li i4a[] = { 0,2l,4l,6l };
    const li i6a[] = { 0,5l };
    li n = 7;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        for (li i6 : i6a) {
                            if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1)
                                continue;
                            for (li i7 = 0; i7 <= n; i7++) {
                                if (i7 == i6 || i7 == i5 || i7 == i4 || i7 == i3 || i7 == i2 || i7 == i1 || !condition7(i5, i6, i7))
                                    continue;
                                for (li i8 = 0; i8 <= n; i8++) {
                                    if (i8 == i7 || i8 == i6 || i8 == i5 || i8 == i4 || i8 == i3 || i8 == i2 || i8 == i1 || !condition8(i6, i7, i8))
                                        continue;
                                    // cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << i8 << endl;
                                    nn++;
                                    li add = li(10000000l * i1)
                                        + li(1000000l * i2)
                                        + li(100000l * i3)
                                        + li(10000l * i4)
                                        + li(1000l * i5)
                                        + li(100l * i6)
                                        + li(10l * i7)
                                        + li(i8);
                                    sum = sum + add;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve6() { // n=6: 7 digits from 0 to 6
    const li i4a[] = { 0,2l,4l,6l };
    const li i6a[] = { 0,5l };
    li n = 6;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        for (li i6 : i6a) {
                            if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1)
                                continue;
                            for (li i7 = 0; i7 <= n; i7++) {
                                if (i7 == i6 || i7 == i5 || i7 == i4 || i7 == i3 || i7 == i2 || i7 == i1 || !condition7(i5, i6, i7))
                                    continue;
                                // cout << i1 << i2 << i3 << i4 << i5 << i6 << i7 << endl;
                                nn++;
                                li add = li(1000000l * i1)
                                    + li(100000l * i2)
                                    + li(10000l * i3)
                                    + li(1000l * i4)
                                    + li(100l * i5)
                                    + li(10l * i6)
                                    + li(i7);
                                sum = sum + add;
                            }
                        }
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve5() { // n=5: 6 digits from 0 to 5
    const li i4a[] = { 0,2l,4l };
    const li i6a[] = { 0,5l };
    li n = 5;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        for (li i6 : i6a) {
                            if (i6 == i5 || i6 == i4 || i6 == i3 || i6 == i2 || i6 == i1)
                                continue;
                            // cout << i1 << i2 << i3 << i4 << i5 << i6 << endl;
                            nn++;
                            li add = li(100000l * i1)
                                + li(10000l * i2)
                                + li(1000l * i3)
                                + li(100l * i4)
                                + li(10l * i5)
                                + li(i6);
                            sum = sum + add;
                        }
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve4() { // n=4: 5 digits from 0 to 4
    const li i4a[] = { 0,2l,4l };
    const li i6a[] = { 0 };
    li n = 4;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    for (li i5 = 0; i5 <= n; i5++) {
                        if (i5 == i4 || i5 == i3 || i5 == i2 || i5 == i1 || !condition5(i3, i4, i5))
                            continue;
                        // cout << i1 << i2 << i3 << i4 << i5 << endl;
                        nn++;
                        li add = li(10000l * i1)
                            + li(1000l * i2)
                            + li(100l * i3)
                            + li(10l * i4)
                            + li(i5);
                        sum = sum + add;
                    }
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

void solve3() { // n=3: 4 digits from 0 to 3
    const li i4a[] = { 0,2l };
    const li i6a[] = { 0 };
    li n = 3;
    li nn = 0;
    li sum = 0;
    for (li i1 = 0; i1 <= n; i1++) {
        for (li i2 = 0; i2 <= n; i2++) {
            if (i2 == i1)
                continue;
            for (li i3 = 0; i3 <= n; i3++) {
                if (i3 == i2 || i3 == i1)
                    continue;
                for (li i4 : i4a) {
                    if (i4 == i3 || i4 == i2 || i4 == i1)
                        continue;
                    // cout << i1 << i2 << i3 << i4 << endl;
                    nn++;
                    li add = li(1000l * i1)
                        + li(100l * i2)
                        + li(10l * i3)
                        + li(i4);
                    sum = sum + add;
                }
            }
        }
    }
    cout << " N = " << n << " count = " << nn << " sum = " << sum << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();
    solve9();
    solve8();
    solve7();
    solve6();
    solve5();
    solve4();
    solve3();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;
    return 0;
}
