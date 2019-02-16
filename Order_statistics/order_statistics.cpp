//
//  main.cpp
//  hw3
//
//  Created by 汪径慈 on 10/23/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
using namespace std;

// function to print out given sequence of length @n
void print_vector(int A[], int n) {
    cout << "{";
    for (int i = 0; i < n; i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}
// function to exchange the value between two integer items
void swap (int *a, int *b) {
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
// function to perform general partition for quicksort
int partition(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i = i + 1;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[r]);
    return i + 1;
}
// give a random number between p and r
int randnum(int p, int r) {
    return rand() % (r-p+1)+ p;
}
// function to perform partition for randomized quicksort
int rand_partition (int A[], int p, int r) {
    int i = randnum(p, r);
    swap(&A[r], &A[i]);
    return partition(A, p, r);
}
// function to perform rand_select algorithm
int rand_select(int A[], int p, int r, int i) {
    if (p == r) {
        return A[p];
    }
    if (p > r) {
        return NULL;
    }
    int q = rand_partition(A, p, r);
    int k = q - p + 1;
    if (k == i) {
        return A[q];
    }else if (k > i) {
        return rand_select(A, p, q - 1, i);
    }else {
        return rand_select(A, q + 1, r, i - k);
    }
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
// find the median of a given array of size @n
int Median(int Arr[], int n) {
    insertion_sort(Arr, n);
    return Arr[n/2];
}
//modified partition for Selection in worst case linear time
int modified_partition(int A[], int p, int r, int x) {
    int i;
    for (i = p; i < r; i++) {
        if (A[i] == x) {
            break;
        }
    }
    swap(&A[r], &A[i]);
    return partition(A, p, r);
}
// function to perform Selection algorithm in worst case linear time
int Select(int A[], int p, int r, int i) {
    if (p == r) {
        return A[p];
    }
    if (p > r) {
        return NULL;
    }
    int n = r - p + 1;
    int median[(n+4)/5];
    int j = 0;
    while (j < n/5) {
        median[j] = Median(A+j*5+p, 5);
        j = j + 1;
    }
    if (j * 5 < n) {
        median[j] = Median(A + j*5 + p, n%5);
        j++;
    }
    int Medofmed;
    if (j == 1) {
        Medofmed = median[0];
    }else{
        Medofmed = Select(median, 0, j-1, j/2);
    }
    int q = modified_partition(A, p, r, Medofmed);
    int k = q - p + 1;
    if (k == i) {
        return A[q];
    }else if (k > i) {
        return Select(A, p, q - 1, i);
    }else{
        return Select(A, q + 1, r, i - k);
    }
}
// generate a random permutation of input {1, 2, ..., 99, 100}
void rand_generate(int A[], int n) {
    random_shuffle(&A[0], &A[n-1]);
}

int main() {
    int A[100];
    clock_t begin, end;
    for (int i = 0; i < 100; i++) {
        A[i] = i + 1;
    }
    rand_generate(A, 100);
    cout << "The random permutation of input for Rand_Select with linear expected running time is generated as follows: " << endl;
    print_vector(A, 100);
    double t[5];
    for (int j = 0; j < 5; j++) {
        int i = randnum(1, 100);
        begin = clock();
        int A_i = rand_select(A, 0, 99, i);
        end = clock();
        cout << "The " << i << "-th smallest number in Array A is " << A_i << endl;
        t[j] = (double) (end - begin) / CLOCKS_PER_SEC;
    }
    double T = (t[0] + t[1] + t[2] + t[3] + t[4]) / 5;
    cout << "The average running time for 5 trials of rand_select algorithm is " << T << endl;
    rand_generate(A, 100);
    cout << "The random permutation of input for Select with linear worst case running time is generated as follows: " << endl;
    print_vector(A, 100);
    for (int j = 0; j < 5; j++) {
        int i = randnum(1, 100);
        begin = clock();
        int A_i = Select(A, 0, 99, i);
        end = clock();
        cout << "The " << i << "-th smallest number in Array A is " << A_i << endl;
        t[j] = (double) (end - begin) / CLOCKS_PER_SEC;
    }
    T = (t[0] + t[1] + t[2] + t[3] + t[4]) / 5;
    cout << "The average running time for 5 trials of select algorithm is " << T << endl;
    return 1;
    
}
