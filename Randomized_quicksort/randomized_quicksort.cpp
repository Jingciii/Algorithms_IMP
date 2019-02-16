//
//  main.cpp
//  hw2-1
//
//  Created by Jingci_Wang on 10/6/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
using namespace std;

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
// function to perform randomized quicksort on A[p, r]
void rand_quicksort (int A[], int p, int r) {
    if (p < r) {
        int q = rand_partition(A, p, r);
        rand_quicksort(A, p, q - 1);
        rand_quicksort(A, q + 1, r);
    }
}
// function to print out given sequence of length @n
void print_vector(int A[], int n) {
    cout << "{";
    for (int i = 0; i < n; i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}

int main() {
    int A[100];
    double run_time[5];
    clock_t begin, end;
    for(int j = 0; j < 5; j++){
        for (int i = 0; i < 100; i++) {
            A[i] = i + 1;
        }
        begin = clock();
        rand_quicksort(A, 0, 99);
        end = clock();
        run_time[j] = (double) (end - begin) / CLOCKS_PER_SEC;
    }
    print_vector(A, 100);
    cout << "The 5 running times for randomized quicksort are: " << endl;
    for (int j = 0; j < 5; j++) {
        cout << run_time[j] << endl;
    }
    return 1;
}
