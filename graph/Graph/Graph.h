#include"MinHeap.h"

#ifndef _GRAPH_H_
#define _GRAPH_H_

// Define the maximum number of vertices in the graph
#define MAX 100

typedef struct Graph *_Graph;
typedef struct Edge *_Edge;
typedef struct Node *_Node;

struct Node
{
    int dest, weight;
    struct Node* next;
};
 
struct Edge {
    int src, dest, weight;
};

struct Graph
{
    // An array of pointers to Node to represent an adjacency list
    _Node head[MAX];
    int Vnum;
    int Enum;
};

_Graph createGraph(struct Edge edges[],int m, int n);
void printGraph(_Graph graph);
void Topological_sort(_Graph graph);
void Dijkstra(_Graph graph, int src);
void DecreaseKey(MinHeap H, int src, int dist);
void Prim(_Graph graph);

#endif