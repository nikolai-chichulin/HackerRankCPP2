#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

typedef long long li;

void solveHR();
void solvePE();
li isTriangle(li tn);
li fromWord(string s);

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    // solve HackerrRank formulation
    // solveHR();

    // solve PE original formulation
    solvePE();

    return 0;
}

void solveHR() {
    int T = 0;
    cin >> T;
    for (int it = 0; it < T; it++) {
        li tn = 0;
        cin >> tn;
        cout << isTriangle(tn) << endl;
    }
}

void solvePE() {

    ifstream inf;
    inf.open("0042_words.txt");
    string tmp;

    int numWords = 0;
    int numTr = 0;
    while (inf >> tmp) {

        numWords++;
        li res = fromWord(tmp);
        li trn = isTriangle(res);
        if (trn != -1) {
            numTr++;
        }

    }
    inf.close();
    cout << numTr << " from " << numWords << endl;
}

li isTriangle(li tn) {
    li D = 1 + 8 * tn;
    li D_05 = li(sqrt(D));
    if (D_05 * D_05 == D) {
        li n = (D_05 - 1) / 2;
        return n;
    }
    else {
        return -1;
    }
}

li fromWord(string s) {
    li ret = 0;
    for (char c : s) {
        li i = li(c - 'A') + 1;
        if (i >= 0 && i <= 26) {
            ret += i;
        }
    }
    return ret;
}
