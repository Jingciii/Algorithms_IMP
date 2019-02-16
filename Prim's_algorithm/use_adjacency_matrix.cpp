//
//  main.cpp
//  hw4
//
//  Created by 汪径慈 on 11/3/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <cstdlib>
using namespace std;

#define Maxnum 100
#define Max_int 999999
int graph[Maxnum][Maxnum] ;
typedef struct MST{
    int g[Maxnum][Maxnum];
}MST;
// function to find the remaining vertex with minimum key value
int findminkey(int keys[], bool mstvetex[], int V){
    int min = Max_int;
    int k = -1;
    for (int v = 0; v < V; v++) {
        if ((keys[v] < min) && (mstvetex[v] == false)) {
            min = keys[v];
            k = v;
        }
    }
    return k;
}
// funtion to ask users to input a graph they want to find MST from
MST creategraph(int V){
    MST G;
    for (int i = 0; i < V; i++) {
        for (int j = i; j < V; j++) {
            cout << "Please enter the weight for the edge connecting vertices " << i+1 << " and " << j+1 << "(if they are not connected, enter 0): " << endl;
            cin >> G.g[i][j];
        }
    }
    for (int j = 0; j < V; j ++) { // fill the symmetric part of the adjacent matrix
        for (int i = 0; i <= j; i++) {
            G.g[j][i] = G.g[i][j];
        }
    }
    for (int i = 0; i < V; i++) { // just to confirm that a vertex would not connect to itself.
        G.g[i][i] = 0;
    }
    return G;
}
// function to initialize adjacent matrix with no pair of vertices connected
MST initial_adj_matrix(int V) {
    MST G;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            G.g[i][j] = 0;
        }
    }
    return G;
}
// function to find MST using Prim's algorithm
MST prim_mst(MST graph, int V){
    int key[V];
    int pi[V];
    bool visited[V];
    for (int i = 1; i < V; i++) {
        key[i] = Max_int;
        visited[i] = false;
    }
    key[0] = 0;
    pi[0] = -1;
    for (int i = 0; i < V-1; i++) {
        int u = findminkey(key, visited, V);
        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (graph.g[u][v] != 0 && visited[v] == false && graph.g[u][v] < key[v]) {
                pi[v] = u;
                key[v] = graph.g[u][v];
            }
        }
    }
    MST G = initial_adj_matrix(V);
    for (int v = 1; v < V; v++) {
        int u = pi[v];
        G.g[u][v] = key[v];
        G.g[v][u] = key[v];
    }
    return G;
}
// function to print adjacent matrix
void print_adj_matrix(MST G, int V){
    for (int i = 0; i < V; i ++) {
        for (int j = 0; j < V; j++) {
            cout << G.g[i][j] << "\t ";
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Please input the size of the MST (i.e., the number of its vertices): ";
    cin >> V;
    MST G = creategraph(V);
    cout << "The adjacent matrix of the original problem we want to find MST from is as follows: " << endl;
    print_adj_matrix(G, V);
    MST adjmat = prim_mst(G, V);
    cout << "The adjacent matrix of the MST found by Prim's algorithm is as follows: " << endl;
    print_adj_matrix(adjmat, V);
    return 0;
}
