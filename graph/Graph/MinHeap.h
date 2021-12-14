#ifndef _MINHEAP_H_
#define _MINHEAP_H_
typedef struct MinHeapNode *Node;
typedef struct MinHeapBody *MinHeap;

struct MinHeapNode
{
  int v;
  int dist;
};
struct MinHeapBody
{
  int size;
  int *pos;
  Node *array;
};

void SwapMinHeapNode(Node *a, Node *b);
Node NewMinHeapNode(int v, int dist);
void HeapifyMin(MinHeap H, int i);
Node DeleteMin(MinHeap H);
int isInMinHeap(MinHeap H, int v);

#endif