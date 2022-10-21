// Statement and information
// Author: Conless
// Date: 2022-10-21
// File name: /algebra/tool/gauss_jordan.cpp

// Headers
#include <bits/stdc++.h>
#include <streambuf>
#include "../include/fraction.h"

// Constants, global variables and definitions

int output_len;

// Templates and namespaces
using namespace std;

int m, n;
Fraction a[100][100];

// Classes

// Funtions
void output() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cout << a[i][j];
            if (output_len >= 8)
                cout << "\t";
            else cout << "\t\t";
        }
        cout << endl;
    }
    cout << endl;
}

// Main function
int main() {
    fstream fs;
    fs.open("../gauss_jordan.in");
    streambuf *cur_cin = cin.rdbuf();
    streambuf *file_cin = fs.rdbuf();
    cin.rdbuf(file_cin);
    cin >> m >> n;
    cout << m << " " << n << endl;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }
    // cin.rdbuf(cur_cin);
    while (true) {
        output();
        char c;
        cin >> c;
        while (c != 'E' && c != 'P' && c != 'D' && c != 'Q')
            cin >> c;
        cout << c << " ";
        if (c == 'E') {
            int r, c;
            cin >> r >> c;
            cout << r << " " << c;
            Fraction div = a[r][c] / a[c][c];
            for (int j = 1; j <= n; j++)
                a[r][j] = a[r][j] - div * a[c][j];
        } else if (c == 'P') {
            int r1, r2;
            cin >> r1 >> r2;
            cout << r1 << " " << r2;
            for (int j = 1; j <= n; j++)
                swap(a[r1][j], a[r2][j]);
        } else if (c == 'D') {
            for (int i = 1; i <= m; i++) {
                Fraction num = a[i][i];
                if (num == 0)
                    continue;
                for (int j = i; j <= n; j++)
                    a[i][j] = a[i][j] / num;
            }
        } else
            break;
        cout << endl;
    }
    cout << endl;
    return 0;
}