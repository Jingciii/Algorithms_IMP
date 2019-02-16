//
//  main.cpp
//  hw4-21
//
//  Created by 汪径慈 on 11/6/18.
//  Copyright © 2018 Jingci_Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define Max_int 999999

// define the node struct to store vertices
typedef struct Node{
    int vertex;
    int key;
    int parent;
}Node;
// define a edge struct to store edge info
typedef struct Edge{
    Node V1;
    Node V2;
    int weight;
}Edge;
typedef pair<Node, int> Pair;
// find whether a node in a vertices set
bool findnode(Node target, vector<Node> nodelist) {
    vector<Node>::iterator iter;
    for (iter = nodelist.begin(); iter != nodelist.end() ; iter++) {
        if (iter->vertex == target.vertex) {
            return true;
        }
    }
    return false;
}
// find whether a edge in the edgeset
bool findedge(Edge edge, vector<Edge> edgeset) {
    vector<Edge>::iterator iter;
    int v1 = edge.V1.vertex;
    int v2 = edge.V2.vertex;
    for (iter = edgeset.begin(); iter != edgeset.end(); iter++) {
        if ((iter->V1.vertex == v1 && iter->V2.vertex == v2) || (iter->V1.vertex == v1 && iter->V2.vertex == v2)) {
            return true;
        }
    }
    return false;
}

// define a class to store the adacent list of a graph
class Graph {
public:
    int V; // number of vertices in the graph
    int E; // number of edges in the graph
    vector<vector<Pair>> adjlist;
    vector<Node> nodeSet;
    vector<Edge> edgeSet;
    Graph(vector<Edge> const &edge, int V) {
        adjlist.resize(V + 1);
        this->V = V;
        this->E = (int)edge.size();
        this->edgeSet = edge;
        for (int e = 0; e < E; e++) {
            Node V1 = edge[e].V1;
            Node V2 = edge[e].V2;
            int weight = edge[e].weight;
            if (weight != 0) {
                Pair p1 = make_pair(V2, weight);
                Pair p2 = make_pair(V1, weight);
                int index1 = V1.vertex;
                int index2 = V2.vertex;
                adjlist[index1].push_back(p1);
                adjlist[index2].push_back(p2);
            }
            // insert nodes into the node set
            if (!findnode(V1, nodeSet)) {
                nodeSet.push_back(V1);
            }
            if (!findnode(V2, nodeSet)) {
                nodeSet.push_back(V2);
            }
        }
    }
};
// function to print the adjacent list
void print_adj_list(Graph const &graph, int V) {
    for (int v = 0; v < V; v++) {
        cout << "Adj[" << v << "]: " << v;
        vector<Pair> alist = graph.adjlist[v];
        int length = (int)graph.adjlist[v].size();
        for (int l = 0; l < length; l++) {
            cout << " --> " << alist[l].first.vertex;
        }
        cout << endl;
    }
}
// function to min-heapify an element in the vector
vector<Node> min_heapify(vector<Node> nodeset, int i, int heap_size){
    vector<Node> nodeSet = nodeset;
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int smallest;
    if ((l <= heap_size - 1) && (nodeSet[l].key < nodeSet[i].key)) {
        smallest = l;
    }else{
        smallest = i;
    }
    if ((r <= heap_size - 1) && (nodeSet[r].key < nodeSet[smallest].key)) {
        smallest = r;
    }
    if (smallest != i) {
        swap(nodeSet[i], nodeSet[smallest]);
        nodeSet = min_heapify(nodeSet, smallest, heap_size);
    }
    return nodeSet;
}
// function to build min-heap
vector<Node> build_min_heap (vector<Node> nodeset, int heap_size){
    vector<Node> nodeSet = nodeset;
    for (int i = (heap_size - 1) / 2; i >=0; i--) {
       nodeSet =  min_heapify(nodeSet, i, heap_size);
    }
    return nodeSet;
}

// function to return the weight of edge connnecting vertex u and v
int weight_uv(Node u, Node v, vector<Edge> edges) {
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].V1.vertex == u.vertex && edges[i].V2.vertex == v.vertex) {
            return edges[i].weight;
        }
        if (edges[i].V1.vertex == v.vertex && edges[i].V2.vertex == u.vertex) {
            return edges[i].weight;
        }
    }
    return 0;
}

// function to extract vertex with minimum key
Node extract_min(vector<Node> nodeSet, int V){
    Node minNode = nodeSet[V-1];
    return minNode;
}
// function to return a node if it is in a given set
Node getnode(vector<Node> nodeSet, int vertex) {
    for (int i = 0; i < nodeSet.size(); i++) {
        if (nodeSet[i].vertex == vertex) {
            return nodeSet[i];
        }
    }
    Node nullnode = {-1, -1, -1};
    return nullnode;
}
// function to find the index of a node in the vector storing given nodes
int findindex(vector<Node> nodeset, Node v){
    int vertex = v.vertex;
    for (int i = 0; i < nodeset.size(); i++) {
        if (nodeset[i].vertex == vertex) {
            return i;
        }
    }
    return -1;
}
// function to perform prim's algorithm
Graph prim_mst(Graph &graph){
    int V = graph.V;
    vector<Node> nodeset = graph.nodeSet;
    vector<Edge> edgeset = graph.edgeSet;
    vector<Edge> updatededge;
    vector<vector<Pair>> adjlist = graph.adjlist;
    nodeset[0].key = 0;
    while (V > 0) {
        nodeset = build_min_heap(nodeset, V);
        swap(nodeset[0], nodeset[V-1]);
        Node u = extract_min(nodeset, V);
        V--;
        vector<Pair> adj_u = adjlist[u.vertex];
        for (int i = 0; i < adj_u.size(); i++) {
            int vertex = adj_u[i].first.vertex;
            Node v = getnode(nodeset, vertex);
            int w = weight_uv(u, v, edgeset);
            if (findnode(v, nodeset)==true && (w < v.key)) {
                int index = findindex(nodeset, v);
                nodeset[index].key = w;
                nodeset[index].parent = u.vertex;
            }
        }
        int parent = u.parent;
        if (parent!= -1) {
            Node pi = getnode(nodeset, parent);
            Edge keptedge;
            keptedge.V1 = u;
            keptedge.V2 = pi;
            keptedge.weight = weight_uv(u, pi, edgeset);
            if (!findedge(keptedge, updatededge)) {
                updatededge.push_back(keptedge);
            }
        }
        }
    Graph mst = Graph(updatededge, graph.V);
    return mst;
}
//function to print weighted edges in the graph
void print_edges(vector<Edge> edgeset) {
    for (int i = 0; i < edgeset.size(); i++) {
        Node u = edgeset[i].V1;
        Node v = edgeset[i].V2;
        int w = edgeset[i].weight;
        cout << "{ (" << u.vertex << ", " << v.vertex << "), weight = " << w << " }" << endl;
    }
}

int main() {
    int V = 9;
    Node node[V];
    for (int i = 0; i < V; i++) {
        node[i] = {i, Max_int, -1};
    }
    vector<Edge> edges =
    {
        {node[0], node[1], 4}, {node[0], node[7], 8}, {node[1], node[7], 11}, {node[1], node[2], 8}, {node[2], node[3], 7}, {node[2], node[8], 2}, {node[2], node[5], 4}, {node[3], node[4], 9}, {node[3], node[5], 14}, {node[5], node[4], 10}, {node[5], node[6], 2}, {node[6], node[7], 1}, {node[6], node[8], 6}, {node[7], node[8], 7}
    };
    Graph graph = Graph(edges, V);
    vector<Node> nodeset = graph.nodeSet;
    cout << "The original graph in adjacency list is as follows: " << endl;
    print_adj_list(graph, V);
    cout << "The weighted edges in the graph are: " << endl;
    print_edges(graph.edgeSet);
    Graph mst = prim_mst(graph);
    cout << "After performing Prim's algorithm, the adjacency list is as follows: " << endl;
    print_adj_list(mst, V);
    cout << "The weighted edges in the MST graph are: " << endl;
    print_edges(mst.edgeSet);
    return 0;
}




