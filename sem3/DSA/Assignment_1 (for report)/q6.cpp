/*
3.6 Define an ADT for Graph.
a) Implement Kruskal’s algorithm for finding the Minimun-Cost Spanning Tree
of a Graph with positive edge-weights.
b) Implement Dijkstra’s algorithm for finding the shortest paths from a start
node to all the other nodes in a graph with positive edge-weights.
c) Write a program to find out the Transitive Closure Matrix for a directed
graph.
*/

#include <queue>
#include <vector>
#include <iostream> 
using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>> graph, int start) { //(dest, wt)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(graph.size(), INT_MAX);
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        pair<int, int> p = pq.top();
        pq.pop();
        for (pair<int, int> edge : graph[p.second]) {
            if (dist[edge.first] > dist[p.second] + edge.second) {
                dist[edge.first] = dist[p.second] + edge.second;
                pq.push({dist[edge.first], edge.first});
            }
        }
    }
    return dist;
}


vector<vector<int>> transitiveClosure(vector<vector<pair<int, int>>> graph) {
    vector<vector<int>> tc(graph.size(), vector<int>(graph.size(), 0));
    for (int i = 0; i < graph.size(); i++) {
        for (pair<int, int> edge : graph[i]) {
            tc[i][edge.first] = 1;
        }
    }
    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                tc[i][j] = tc[i][j] | (tc[i][k] & tc[k][j]);
            }
        }
    }

    return tc;
}


class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void unionSet(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return;
        }
        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {            
            parent[y] = x;
            rank[x]++;
        }
    }
};


void kruskal(vector<vector<pair<int, int>>> graph) { // (dest, wt)
    DisjointSet ds(graph.size());
    vector<pair<int, int>> mst;
    for (int i = 0; i < graph.size(); i++) {
        for (pair<int, int> edge : graph[i]) {
            if (ds.find(i) != ds.find(edge.first)) {
                mst.push_back(edge);
                ds.unionSet(i, edge.first);
            }
        }
    }
    for (pair<int, int> edge : mst) {
        cout << edge.first << " -> " << edge.second << '\n';
    }
}


int main() {
    
}
