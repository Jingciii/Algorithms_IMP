//
//  main.cpp
//  hw32
//
//  Created by 汪径慈 on 10/23/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// Build a table to record the optimal solution for subarray
typedef struct table{
    string b[100][100];
    int c[100][100];
}table;

// Function to find the longest common subsequence by dynamic programming. It will return the table recording optimal solution for subarray
table LCS_length(char X[][2], char Y[][2], int m, int n){
    table T;
    for (int i = 0; i <= m; i++) {
        T.c[i][0] = 0;
    }
    for (int j = 0; j <= n; j++) {
        T.c[0][j] = 0;
    }
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (strcmp(X[i-1], Y[j-1]) == 0) {
                T.c[i][j] = T.c[i-1][j-1] + 1;
                T.b[i][j] = "upperleft";
            }else if (T.c[i-1][j] >= T.c[i][j-1]){
                T.c[i][j] = T.c[i-1][j];
                T.b[i][j] = "upper";
            }else{
                T.c[i][j] = T.c[i][j-1];
                T.b[i][j] = "left";
            }
        }
    }
    return T;
}
// Function to print the reference table for solution of subarray
void print_LCS(string b[][100], char X[][2], int i, int j) {
    if (i == 0 || j == 0) {
        return;
    }
    if (b[i][j] == "upperleft") {
        print_LCS(b, X, i-1, j-1);
        cout << X[i-1] << " ";
    }else if (b[i][j] == "upper") {
        print_LCS(b, X, i-1, j);
    }else{
        print_LCS(b, X, i, j-1);
    }
}

int main() {
    int m = 7;
    int n = 6;
    clock_t begin, end;
    char X[][2] = {"A", "B", "C", "B", "D", "A", "B"};
    char Y[][2] = {"B", "D", "C", "A", "B", "A"};
    begin = clock();
    table T = LCS_length(X, Y, m, n);
    end = clock();
    double t = (double) (end - begin) / CLOCKS_PER_SEC;
    cout << "The C table computed by LCS-length on sequences X and Y is presented as follows:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << T.c[i][j] << "\t";
        }
        cout << endl;
    }
    cout <<endl << "The B table computed by LCS-length on sequences X and Y is presented as follows from which we can trace the optimal subproblem solution:" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << T.b[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "The LCS of X and Y is: ";
    print_LCS(T.b, X, m, n);
    cout << endl;
    cout << "The running time for computing the LCS-length in this case is " << t << endl;
    return 1;
}
