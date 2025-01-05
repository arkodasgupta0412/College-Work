/*
3.6 Define an ADT for Graph.
a) Implement Kruskal’s algorithm for finding the Minimun-Cost Spanning Tree
of a Graph with positive edge-weights.
b) Implement Dijkstra’s algorithm for finding the shortest paths from a start
node to all the other nodes in a graph with positive edge-weights.
c) Write a program to find out the Transitive Closure Matrix for a directed
graph.
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int *parent;
    int *rank;
    int size;
} DisjointSet;

DisjointSet* createDisjointSet(int n) {
    DisjointSet *ds = (DisjointSet *)malloc(sizeof(DisjointSet));
    ds->parent = (int *)malloc(n * sizeof(int));
    ds->rank = (int *)malloc(n * sizeof(int));
    ds->size = n;

    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
    return ds;
}

int findParent(DisjointSet *ds, int u) {
    if (u != ds->parent[u]) {
        ds->parent[u] = findParent(ds, ds->parent[u]);
    }
    return ds->parent[u];
}

void unionByRank(DisjointSet *ds, int u, int v) {
    u = findParent(ds, u);
    v = findParent(ds, v);

    if (u != v) {
        if (ds->rank[u] > ds->rank[v]) {
            ds->parent[v] = u;
        } else if (ds->rank[u] < ds->rank[v]) {
            ds->parent[u] = v;
        } else {
            ds->parent[u] = v;
            ds->rank[v]++;
        }
    }
}

typedef struct {
    int u, v, weight;
} Edge;

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(Edge edges[], int V, int E) {
    qsort(edges, E, sizeof(Edge), compareEdges);
    DisjointSet *ds = createDisjointSet(V);

    int cost = 0;
    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        if (findParent(ds, u) != findParent(ds, v)) {
            unionByRank(ds, u, v);
            cost += weight;
            printf("%d -- %d == %d\n", u, v, weight);
        }
    }

    printf("Cost: %d\n", cost);
    free(ds->parent);
    free(ds->rank);
    free(ds);
}

typedef struct {
    int node, distance;
} PQNode;

typedef struct {
    PQNode *nodes;
    int size, capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->nodes = (PQNode *)malloc(capacity * sizeof(PQNode));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(PQNode *a, PQNode *b) {
    PQNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue *pq, int node, int distance) {
    if (pq->size >= pq->capacity) return;
    pq->nodes[pq->size++] = (PQNode){node, distance};

    int i = pq->size - 1;
    while (i > 0 && pq->nodes[i].distance < pq->nodes[(i - 1) / 2].distance) {
        swap(&pq->nodes[i], &pq->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

PQNode pop(PriorityQueue *pq) {
    PQNode root = pq->nodes[0];
    pq->nodes[0] = pq->nodes[--pq->size];

    int i = 0;
    while (true) {
        int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < pq->size && pq->nodes[left].distance < pq->nodes[smallest].distance) {
            smallest = left;
        }
        if (right < pq->size && pq->nodes[right].distance < pq->nodes[smallest].distance) {
            smallest = right;
        }
        if (smallest == i) break;
        swap(&pq->nodes[i], &pq->nodes[smallest]);
        i = smallest;
    }
    return root;
}

bool isEmpty(PriorityQueue *pq) {
    return pq->size == 0;
}

void dijkstra(int **graph, int V, int start) {
    PriorityQueue *pq = createPriorityQueue(V);
    int *dist = (int *)malloc(V * sizeof(int));
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;

    dist[start] = 0;
    push(pq, start, 0);

    while (!isEmpty(pq)) {
        PQNode node = pop(pq);
        int u = node.node;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                push(pq, v, dist[v]);
            }
        }
    }

    printf("Shortest Distances from Node %d:\n", start);
    for (int i = 0; i < V; i++) {
        printf("Node %d: %d\n", i, dist[i]);
    }

    free(dist);
    free(pq->nodes);
    free(pq);
}

void transitiveClosure(int **graph, int V) {
    int **closure = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        closure[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            closure[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }

    printf("Transitive Closure:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", closure[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < V; i++) {
        free(closure[i]);
    }
    free(closure);
}

int main() {
    int V = 3, E = 3;

    Edge edges[] = {
        {0, 1, 2},
        {1, 2, 3},
        {0, 2, 1}
    };

    printf("Kruskal's Algorithm:\n");
    kruskal(edges, V, E);

    int **graph = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        graph[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            graph[i][j] = 0;
        }
    }

    graph[0][1] = 2;
    graph[1][2] = 3;
    graph[0][2] = 1;

    printf("\nDijkstra's Algorithm:\n");
    dijkstra(graph, V, 0);

    printf("\nTransitive Closure:\n");
    transitiveClosure(graph, V);

    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
