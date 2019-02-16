//
//  main.cpp
//  hw5
//
//  Created by 汪径慈 on 12/7/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

#define inf 999999.0

// define a struct to store node, initializing its parent to be -1
typedef struct Node {
    int index;
    double d;
    vector<int> adj;
    int pi = -1;
}Node;
// define a struct to store directed edge
typedef struct Edge {
    Node from;
    Node to;
    double weight;
} Edge;

// funtion to return whether a node is the adjacent to another
bool find_adj(Node v, int id) {
    if (v.adj.empty()) {
        return false;
    }
    for (int i = 0; i < v.adj.size(); i++) {
        if (v.adj[i] == id) {
            return true;
        }
    }
    return false;
}

// define a class to operate Dijstra's algorithm
class Dijstra {
public:
    vector<Node> V;
    vector<Edge> E;
    
    Dijstra(vector<Node> V, vector<Edge> E){
        this->V = V;
        this->E = E;
    }
    double weight(Node V1, Node V2) {
        for (int i = 0; i < this->E.size(); i++) {
            if (E[i].from.index == V1.index && E[i].to.index == V2.index) {
                return E[i].weight;
            }
        }
        return inf;
    }
    void initial_single_source(Node s) {
        for (int i = 0; i < this->V.size(); i++) {
            if (this->V[i].index == s.index) {
                this->V[i].d = 0;
            }else {
                this->V[i].d = inf;
            }
        }
    }
    void relax(Node &u, Node &v, double w) {
        if (v.d > u.d + w) {
            v.d = u.d + w;
            v.pi = u.index;
        }
    }
    void dijkstra(Node s){
        vector<Node> S;
        vector<Node> Q;
        this->initial_single_source(s);
        for (int i = 0; i < this->V.size(); i++) {
            Q.push_back(this->V[i]);
        }
        while (Q.empty() == false) {
            double min_d = inf;
            Node u;
            cout << endl;
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i].d < min_d) {
                    u = Q[i];
                    min_d = Q[i].d;
                }
            }
            S.push_back(u);
            for (int i = 0; i < Q.size(); i++) {
                if (find_adj(u, Q[i].index)) {
                    this->relax(u, this->V[Q[i].index], this->weight(u, this->V[Q[i].index]));
                    this->relax(u, Q[i], this->weight(u, Q[i]));
                }
            }
            for (int i = 0; i < Q.size(); i++) {
                if (Q[i].index == u.index) {
                    swap(Q[i], Q[(int)Q.size() - 1]);
                }
            }
            Q.pop_back();
        }
    }
};

int main() {
    Node v0 = {0, inf, {1, 2}};
    Node v1 = {1, inf, {2, 3}};
    Node v2 = {2, inf, {1, 3, 4}};
    Node v3 = {3, inf, {4}};
    Node v4 = {4, inf, {0, 3}};
    vector<Node> v;
    v.push_back(v0);
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);
    Edge e1 = {v0, v1, 10};
    Edge e2 = {v0, v2, 5};
    Edge e3 = {v1, v2, 2};
    Edge e4 = {v2, v1, 3};
    Edge e5 = {v1, v3, 1};
    Edge e6 = {v2, v3, 9};
    Edge e7 = {v2, v4, 2};
    Edge e8 = {v3, v4, 4};
    Edge e9 = {v4, v3, 6};
    Edge e10 = {v4, v0, 7};
    vector<Edge> e;
    e.push_back(e1);
    e.push_back(e2);
    e.push_back(e3);
    e.push_back(e4);
    e.push_back(e5);
    e.push_back(e6);
    e.push_back(e7);
    e.push_back(e8);
    e.push_back(e9);
    e.push_back(e10);
    Dijstra task = Dijstra(v, e);
    task.dijkstra(task.V[0]);
    for (int i = 0; i < task.V.size(); i++) {
        cout << "Node" << i << ": d[" << i << "] = " << task.V[i].d << " pi[" << i <<"] = " << task.V[i].pi << endl;
    }
    
    return 0;
}
