#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "MinHeap.h"

#define Unlimited 99999

_Graph createGraph(struct Edge edges[], int m, int n)
{
    _Graph graph = (_Graph)malloc(sizeof(struct Graph));

    //初始化头节点数组的边链表
    for (int i = 0; i < MAX; i++)
    {
        graph->Vnum = m;
        graph->Enum = n;
        graph->head[i] = NULL;
    }

    //将边一一添加到有向图
    for (int i = 0; i < graph->Enum; i++)
    {
        //获取源顶点和目标顶点
        int src = edges[i].src;
        int dest = edges[i].dest;
        int weight = edges[i].weight;

        //创造一个标志着从'src'指向'dest'的边的节点
        _Node newNode = (_Node)malloc(sizeof(struct Node));
        newNode->dest = dest;
        newNode->weight = weight;

        //将新生成的链表节点插入到对应头节点后的链表上
        newNode->next = graph->head[src];
        graph->head[src] = newNode;
    }

    return graph;
}

void printGraph(_Graph graph)
{
    for (int i = 0; i < graph->Vnum; i++)
    {
        int flag = 1;
        _Node ptr = graph->head[i];
        while (ptr != NULL)
        {
            flag=0;
            printf("%d —> %d (%d)\t", i, ptr->dest, ptr->weight);
            ptr = ptr->next;
        }
        if(flag)
        {
            printf("%d —> NULL\n", i);
        }
        else
        {
            printf("\n");
        }
    }
    printf("\n");
}

void Topological_sort(_Graph graph)
{
    int Indegree[graph->Vnum], count = 0, i;
    _Node ptr;
    for (int i = 0; i < graph->Vnum; i++)
    {
        Indegree[i] = 0;
    }
    
    int *quene = (int *)malloc((graph->Vnum) * sizeof(int)); // 辅助队列
    int front = 0;
    int rear = 0;

    for (i = 0; i < graph->Vnum; i++)
    {
        ptr = graph->head[i];
        while (ptr != NULL)
        {
            Indegree[ptr->dest]++;
            ptr = ptr->next;
        }
    }

    //将所有入度为0的点放入容器中
    for (i = 0; i < graph->Vnum; i++)
    {
        if (Indegree[i] == 0)
        {
            quene[rear++] = i;
        }
    }

    printf("Topological sorting result of graph:\n");
    while (front != rear)
    {
        int j = quene[front++];
        printf("%4d", j);
        count++;
        ptr = graph->head[j];
        while (ptr != NULL)
        {
            Indegree[ptr->dest]--;
            if (Indegree[ptr->dest] == 0)
            {
                quene[rear++] = ptr->dest;
            }
            ptr = ptr->next;
        }
    }
    if (count < graph->Vnum)
    {
        printf("Graph has a cycle\n");
    }
    free(quene);
}

void printDijkstra(int dist[], int n)
{
    printf("\nVertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        if(dist[i]!=Unlimited)
            printf("%d \t %d\n", i, dist[i]);
        else
            printf("%d \t UnLimited\n", i);
}

void printPrim(int arr[], int n)
{
    printf("The minimum spanning tree edge of the graph is\n");
    for (int i = 1; i < n; ++i)
        printf("%d - %d\n", arr[i], i);
}

void Dijkstra(_Graph graph, int src)
{
    int dist[graph->Vnum];

    MinHeap H = (MinHeap)malloc(sizeof(struct MinHeapBody));
    H->pos = (int *)malloc(graph->Vnum * sizeof(int));
    H->array = (Node *)malloc(graph->Vnum * sizeof(Node));

    //对于所有图节点初始化最小堆
    for (int i = 0; i < graph->Vnum; ++i)
    {
        dist[i] = Unlimited;
        H->array[i] = NewMinHeapNode(i, dist[i]);
        H->pos[i] = i;
    }

    H->array[src] = NewMinHeapNode(src, dist[src]);
    H->pos[src] = src;
    dist[src] = 0;
    DecreaseKey(H, src, dist[src]);
    H->size = graph->Vnum;

    // 在下面的循环中，最小堆包含最短距离尚未确定的所有节点。
    while (H->size != 0)
    {
        Node MinNode = DeleteMin(H);
        int u = MinNode->v;
        // 遍历u的所有相邻顶点（提取顶点）并更新它们的距离值
        _Node p = graph->head[u];

        while (p != NULL)
        {
            int v = p->dest;
            //如果到 v 的最短距离尚未最终确定，并且到 v 到 u 的距离小于其先前计算的距离
            if (isInMinHeap(H, v) && dist[u] != Unlimited && p->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + p->weight;
                DecreaseKey(H, v, dist[v]);
            }
            p = p->next;
        }
    }
    printDijkstra(dist, graph->Vnum);
}

void Prim(_Graph graph)
{
    int parent[graph->Vnum];
    int key[graph->Vnum];          

    MinHeap H = (MinHeap)malloc(sizeof(struct MinHeapBody));
    H->pos = (int *)malloc(graph->Vnum * sizeof(int));
    H->array = (Node *)malloc(graph->Vnum * sizeof(Node));

    for (int v = 1; v < graph->Vnum; ++v)
    {
        parent[v] = -1;
        key[v] = Unlimited;
        H->array[v] = NewMinHeapNode(v, key[v]);
        H->pos[v] = v;
    }

    // 将第0个顶点的key值设为0，以便先提取
    key[0] = 0;
    H->array[0] = NewMinHeapNode(0, key[0]);
    H->pos[0] = 0;

    H->size = graph->Vnum;

    while (H->size != 0)
    {
        Node minHeapNode = DeleteMin(H);
        int u = minHeapNode->v; //存储提取的顶点号

        // 遍历u的所有相邻顶点（提取的顶点）并更新它们的键值
        _Node p = graph->head[u];
        while (p != NULL)
        {
            int v = p->dest;

            //如果到 v 的最短距离尚未最终确定，并且到 v 到 u 的距离小于其先前计算的距离
            if (isInMinHeap(H, v) && p->weight < key[v])
            {
                key[v] = p->weight;
                parent[v] = u;
                DecreaseKey(H, v, key[v]);
            }
            p = p->next;
        }
    }
    printPrim(parent, graph->Vnum);
}