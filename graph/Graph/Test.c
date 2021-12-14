#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "MinHeap.h"

int main()
{
    // struct Edge edges[] =
    // {
    //     {0, 4, 4}, {0, 1, 6}, {1, 4, 2}, {1, 5, 10}, {4, 3, 3}, {3, 5, 1}, {1, 6, 5},
    //     {5, 2, 8}, {6, 2, 6}
    // };

    // int m = 7;
    // int n = sizeof(edges)/sizeof(edges[0]);
    //  _Graph graph = createGraph(edges, m, n);

    int VertexNum, EdgeNum;

    scanf("%d %d", &VertexNum, &EdgeNum);
    getchar();
    struct Edge edges[EdgeNum];
    for (int i = 0; i < EdgeNum; i++)
    {
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);
        getchar();
    }

    _Graph graph = createGraph(edges, VertexNum, EdgeNum);
    
    printGraph(graph);
    Topological_sort(graph);

    Dijkstra(graph, 0);
    Prim(graph);
    return 0;
}