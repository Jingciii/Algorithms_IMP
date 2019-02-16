//
//  main.cpp
//  hw1
//
//  Created by Jingci Wang on 9/21/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <time.h>
using namespace std;

//Function to print out given sequence of length @n
void print_vector(int A[], int n) {
    cout << "{";
    for (int i = 0; i < n; i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}

//Function to operate insertion sort on the given sequence @A of length @n
void insertion_sort(int A[], int n) {
    for (int j = 1; j < n; j++) {
        int key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i+1] = A[i];
            i = i - 1;
        }
        A[i+1] = key;
    }
}
//Auxiliary procedure to merge the sorted subsequence
//@A[p:q] and @A[q+1, r] to produce the sorted answer
void merge(int A[], int p, int q, int r) {
    int n_1 = q - p + 1;
    int n_2 = r - q;
    int L[n_1];
    int R[n_2];
    for (int i = 0; i < n_1; i++) {
        L[i] = A[p+i];
    }
    for (int j = 0; j < n_2; j++) {
        R[j] = A[q+j+1];
    }
    int i = 0;
    int j = 0;
    int k = p;
    while (i < n_1 && j < n_2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
            k++;
        }else{
            A[k] = R[j];
            j++;
            k++;
        }
    }
    while (i < n_1) {
        A[k] = L[i];
        k++;
        i++;
    }
    while (j < n_2) {
        A[k] = R[j];
        k++;
        j++;
    }
}
//Function to perform mergesort with sequence @A[p:r]
void mergesort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergesort(A, p, q);
        mergesort(A, q+1, r);
        merge(A, p, q, r);
    }
}

//Auxiliary functions for generating worst-case sequence for mergesort with
//@L[] the left part of original sequence, @R[] the right part of original sequence
//@l the left-end index, @r the right-end index, @m the middle index
void worstcase_join(int A[], int L[], int R[], int l, int r, int m) {
    int i = 0;
    for (i = 0; i < m-l+1; i++) {
        A[i] = L[i];
    }
    for (int j = 0; j < r-m; j++) {
        A[i+j] = R[j];
    }
}
void worstcase_seperate(int A[], int L[], int R[], int l, int r, int m) {
    for (int i = 0; i < m-l+1; i++) {
        L[i] = A[i*2];
    }
    for (int j = 0; j < r-m; j++) {
        R[j] = A[j*2+1];
    }
}
//Function to generate worst-case for mergesort with sequence @A[p:r]
void generateworstcase(int A[], int p, int r) {
    if (r > p){
        int q = p + (r - p)/2;
        int L[q - p + 1];
        int R[r - q];
        worstcase_seperate(A, L, R, p, r, q);
        generateworstcase(L, p, q);
        generateworstcase(R, q+1, r);
        worstcase_join(A, L, R, p, r, q);
    }
}

int main(int argc, const char * argv[]) {
    clock_t start_1, end_1;
    clock_t start_2, end_2;
    int n = 0;
    double compare = 1;
    double t_1 = 0;
    double t_2 = 0;
    while (compare > -1e-5) {
        n = n + 1;
        int A[n];
        int B[n];
        for (int i = 0; i < n; i++) {
            A[i] = n - i;   // generate worst-case for insertion sort
            B[i] = i + 1;
        }
        cout << "When input size equals to " << n << ", permutation that causes worst case for insertion sort is: " << endl;
        print_vector(A, n);
        generateworstcase(B, 0, n-1);  // generate worst-case for mergesort
        cout << "When input size equals to " << n << ", permutation that causes worst case for mergesort is: " << endl;
        print_vector(B, n);
        start_1 = clock();
        insertion_sort(A, n);
        end_1 = clock();
        t_1 = (double)(end_1 - start_1) / CLOCKS_PER_SEC; //running time for insertion sort
        start_2 = clock();
        mergesort(B, 0, n-1);
        end_2 = clock();
        t_2 = (double)(end_2 - start_2) / CLOCKS_PER_SEC; //running time for mergesort
        compare = t_2 - t_1;
    }
    cout << "The input size that mergesort starts to beat insertion sort in terms of worst-case running time is: " << n << endl;
    cout << "The worst-case running time of insertion sort for input size " << n << " is: " << t_1<< endl;
    cout << "The worst-case running time of mergesort for input size " << n << " is: " << t_2 << endl;
    return 0;
}
