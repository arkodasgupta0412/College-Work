/*
3.6 Define an ADT for Graph.
a) Implement Kruskal’s algorithm for finding the Minimun-Cost Spanning Tree
of a Graph with positive edge-weights.
b) Implement Dijkstra’s algorithm for finding the shortest paths from a start
node to all the other nodes in a graph with positive edge-weights.
c) Write a program to find out the Transitive Closure Matrix for a directed
graph.
*/


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;


class DisjointSet {
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int findParent(int u) {
        if (u != parent[u]) {
            parent[u] = findParent(parent[u]);
        }

        return parent[u];
    }

    void unionByRank(int u, int v) {
        u = findParent(u);
        v = findParent(v);

        if (u == v) {
            return;
        }

        if (rank[u] > rank[v]) {
            parent[v] = u;
        } else if (rank[u] < rank[v]) {
            parent[u] = v;
        } else {
            parent[u] = v;
            rank[v]++;
        }
    }
};


vector<pair<int, int>> kruskal(vector<pair<int, int>> graph, int V) { // (dest, wt)
    sort(graph.begin(), graph.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.second < b.second;
    });
    
    DisjointSet ds(V);
    vector<pair<int, int>> mst;
    int cost = 0;

    for (pair<int, int> edge : graph) {
        int u = edge.first;
        int v = edge.second;
        if (ds.findParent(u) != ds.findParent(v)) {
            ds.unionByRank(u, v);
            mst.push_back(edge);
            cost += edge.second;
        }
    }
    cout << "Cost: " << cost << '\n';
    return mst;
}


vector<int> dijkstra(vector<vector<pair<int, int>>> graph, int start) { //(dest, wt)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; //(dist, node) -> min heap
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


vector<vector<int>> transitiveClosure(vector<vector<int>> graph) {
    vector<vector<int>> closure = graph;
    for (int k = 0; k < graph.size(); k++) {
        for (int i = 0; i < graph.size(); i++) {
            for (int j = 0; j < graph.size(); j++) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }
    return closure;
}


int main() {
    vector<vector<pair<int, int>>> graph = {
        {{1, 2}, {2, 3}},
        {{0, 2}, {2, 1}},
        {{0, 3}, {1, 1}}
    };

    cout << "Kruskal's Algorithm\n";
    vector<pair<int, int>> mst = kruskal({
        {0, 2},
        {1, 2},
        {2, 1},
        {0, 3},
        {1, 1}
    }, 3);
    for (pair<int, int> edge : mst) {
        cout << edge.first << " -> " << edge.second << '\n';
    }

    cout << "\nDijkstra's Algorithm\n";
    vector<int> dist = dijkstra(graph, 0);
    for (int i = 0; i < dist.size(); i++) {
        cout << "0 -> " << i << ": " << dist[i] << '\n';
    }

    cout << "\nTransitive Closure\n";
    vector<vector<int>> closure = transitiveClosure({
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}
    });
    for (int i = 0; i < closure.size(); i++) {
        for (int j = 0; j < closure.size(); j++) {
            cout << closure[i][j] << ' ';
        }
        cout << '\n';
    }    

    return 0;
}