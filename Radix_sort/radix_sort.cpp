//
//  main.cpp
//  hw2-4
//
//  Created by 汪径慈 on 10/6/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;
using std::vector;

// function to find the max element from a given array of length n
int max(vector<int> &A) {
    int n = (int) A.size();
    int max_ele = A[0];
    for (int i = 0; i < n; i++) {
        if (max_ele < A[i]) {
            max_ele = A[i];
        }
    }
    return max_ele;
}
// revise counting sort function from the previous problem
void counting_sort(vector<int> &A, int exp) {
    vector<int> C(10, 0);
    int A_size = (int) A.size();
    vector<int> B(10);
    for (int j = 0; j < A_size; j++) {
        int e = (A[j]/exp) % 10;
        C[e]++;
    }
    for (int i = 1; i < 10; i++) {
        C[i] = C[i] + C[i-1];
    }
    for (int j = A_size - 1; j >= 0; j--) {
        int aj = (A[j]/exp) % 10;
        int caj = C[aj];
        B[caj - 1] = A[j];
        C[aj] = C[aj] - 1;
    }
    for (int i = 0; i < A_size; i++) {
        A[i] = B[i];
    }
}
// function to perform radix sort using the counting sort above
void radixsort(vector<int> &A) {
    int m = max(A);
    for (int exp = 1; m/exp > 0; exp *= 10) {
        counting_sort(A, exp);
    }
}
// function to print out given vector
void print_vector(vector<int> &A) {
    cout << "{";
    for (int i = 0; i < (int)A.size(); i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}

int main(int argc, const char * argv[]) {
    clock_t begin, end;
    vector<int> A = {329, 457, 657, 839, 436, 720, 353};
    begin = clock();
    radixsort(A);
    end = clock();
    double run_time = (double) (end - begin) / CLOCKS_PER_SEC;
    cout << "The output sequence ordered by radix sort is listed as follows: " << endl;
    print_vector(A);
    cout << "The running time for radix sort of input size 7 is: " << run_time << endl;
}
