//
//  main.cpp
//  hw2-2
//
//  Created by 汪径慈 on 10/6/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <algorithm> // include random_shuffle
using namespace std;

// function to exchange the value between two integer items
void swap (int &a, int &b) {
    a = a + b;
    b = a - b;
    a = a - b;
}
// function to print out given sequence of length @n
void print_vector(int A[], int n) {
    cout << "{";
    for (int i = 0; i < n; i++) {
        cout << " " << A[i];
    }
    cout << " " << "}" << endl;
}
// function to perform max_heapify on the ith element
// assuming that its left and right subtrees are already max heapified
void max_heapify (int A[], int i, int heap_size) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest;
    if (l <= heap_size-1 && A[l] > A[i]) {
        largest = l;
    }else{
        largest = i;
    }
    if (r <= heap_size-1 && A[r] > A[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(A[i], A[largest]);
        max_heapify(A, largest, heap_size);
    }
}
// building a heap
void build_max_heap (int A[], int heap_size) {
    for (int i = (heap_size - 1) / 2; i >= 0; i--) {
        max_heapify(A, i, heap_size);
    }
}

// function to perform heapsort
void heapsort (int A[], int heap_size) {
    build_max_heap(A, heap_size);
    for (int i = heap_size; i > 1; i--) {
        swap(A[0], A[i - 1]);
        max_heapify(A, 0, i - 1);
    }
}
// generate a random permutation of input {1, 2, ..., 99, 100}
void rand_generate(int A[], int n) {
    random_shuffle(&A[0], &A[n-1]);
}

int main(int argc, const char * argv[]) {
    int A[100];
    clock_t begin, end;
    for (int i = 0; i < 100; i++) {
        A[i] = i + 1;
    }
    rand_generate(A, 100);
    cout << "The random permutation of input is generated as follows: " << endl;
    print_vector(A, 100);
    begin = clock();
    heapsort(A, 100);
    end = clock();
    double run_time = double (end - begin) / CLOCKS_PER_SEC;
    cout << "The output of heapsort is as follows: " << endl;
    print_vector(A, 100);
    cout << "The running time for heapsort is " << run_time << endl;
    return 1;
}
