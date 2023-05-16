#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <map>
#include <set>

using namespace std;

/// <summary>
/// Check if a is less than b, assuming a and b are representing integers.
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
bool lessthan(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size();
    }
    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return false;
}

string sum(const string& a, const string& b) {
    string ret;
    int la = static_cast<int>(a.size());
    int lb = static_cast<int>(b.size());
    int lmin = min(la, lb);
    int lmax = max(la, lb);
    int c = 0;
    for (int i = 0; i < lmin; i++) {
        int ia = la - 1 - i;
        int ib = lb - 1 - i;
        int res = (a[ia] - '0') + (b[ib] - '0') + c;
        int rem = res % 10;
        c = res / 10;
        ret.insert(ret.begin(), '0' + rem);
    }
    if (la != lb) {
        bool aig = la >= lb;
        for (int i = lmin; i < lmax; i++) {
            int ia = la - 1 - i;
            int ib = lb - 1 - i;
            int res = (aig ? a[ia] : b[ib]) - '0' + c;
            int rem = res % 10;
            c = res / 10;
            ret.insert(ret.begin(), '0' + rem);
        }
    }
    if (c > 0) {
        ret.insert(ret.begin(), '0' + c);
    }
    return ret;
}

/// <summary>
/// Performs the main 196 operation: adds the palindrome of the given number.
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
string addpal(const string& a) {
    string ret;
    int la = static_cast<int>(a.size());
    int c = 0;
    for (int i = 0; i < la; i++) {
        int ia = la - 1 - i;
        int ib = i;
        int res = (a[ia] - '0') + (a[ib] - '0') + c;
        int rem = res % 10;
        c = res / 10;
        ret.insert(ret.begin(), '0' + rem);
    }
    if (c > 0) {
        ret.insert(ret.begin(), '0' + c);
    }
    return ret;
}

bool ispal(const string& s) {
    for (int i = 0; i < s.size() / 2; i++) {
        if (s[i] != s[s.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

pair<int, string> findpal(const string& s) {

    // This condition depends on the problem statement!
    // A palindrom itself is considered non-Lychrel for HackerRank
    // For the original PE55 it is not.
    if (ispal(s)) {
        return pair<int, string>(0, s);
    }

    string ss = s;
    int iter = 0;
    int maxiter = 60;
    iter++;
    ss = addpal(ss);
    while (!ispal(ss)) {
        iter++;
        if (iter == maxiter) {
            return pair<int, string>(-1, "");
        }
        ss = addpal(ss);
    }
    return pair<int, string>(iter, ss);
}

void solvePE() {
    string s = "";
    string d = "1";
    string res = sum(s, d);
    int nlych = 0;
    while (lessthan(res, "130")) {
        pair<int, string> ttt = findpal(res);
        int iter = ttt.first;
        if (iter == -1) {
            nlych++;
        }
        res = sum(res, d);
    }
    cout << "Nlych = " << nlych << endl;
}

void solveHR() {
    string s = "";
    string d = "1";
    s = sum(s, d);
    int nlych = 0;
    map<string, int> pals;
    while (lessthan(s, "130")) {
        pair<int, string> res = findpal(s);
        int iter = res.first;
        if (iter == -1) {
            nlych++;
        }
        else {
            pals[res.second]++;
        }
        s = sum(s, d);
    }

    string maxpal;
    int maxnum = 0;
    for (auto& p : pals) {
        if (p.second > maxnum) {
            maxnum = p.second;
            maxpal = p.first;
        }
    }
    // std::cout << "The most popular palyndrome = " << maxpal << " with " << maxnum << " children" << endl;
    // std::cout << "Nlych = " << nlych << endl;
    std::cout << maxpal << " " << maxnum << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    auto start = std::chrono::high_resolution_clock::now();

    //string s1 = "12677";
    //string s2 = "10677";
    //cout << lessthan(s1, s2) << endl;
    //findpal(s);

    solveHR();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double t = duration.count() / 1E6;
    cout << "Execution time    = " << t << " s" << endl;

    return 0;
}
