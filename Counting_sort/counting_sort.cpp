//
//  main.cpp
//  hw2-3
//
//  Created by 汪径慈 on 10/6/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
using std::vector;

// function to print out given vector
void print_vector(vector<int> &A) {
    cout << "{";
    for (int i = 0; i < (int)A.size(); i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}
// function to perform counting sort
void counting_sort(vector<int> &A, vector<int> &B, int k) {
    vector<int> C(k+1, 0);
    int A_size = (int) A.size();
    for (int j = 0; j < A_size; j++) {
        int e = A[j];
        C[e]++;
    }
    for (int i = 1; i <= k; i++) {
        C[i] = C[i] + C[i-1];
    }
    for (int j = A_size - 1; j >= 0; j--) {
        int aj = A[j];
        int caj = C[aj];
        B[caj - 1] = A[j];
        C[aj] = C[aj] - 1;
    }
}

int main() {
    clock_t begin, end;
    vector<int> A = {20, 18, 5, 7, 10, 9, 3, 12, 14, 0};
    vector<int> B(A.size(), 0);
    begin = clock();
    counting_sort(A, B, 20);
    end = clock();
    double run_time = (double) (end - begin) /CLOCKS_PER_SEC;
    print_vector(B);
    cout << "The running time for counting sort is: " << run_time << endl;
    return 1;
}
