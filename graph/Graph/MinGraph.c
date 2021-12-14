#include<stdio.h>
#include<stdlib.h>
#include "MinHeap.h"

void SwapMinHeapNode(Node *a, Node *b)
{

  Node t = *a;
  *a = *b;
  *b = t;
}

Node NewMinHeapNode(int v, int dist)
{
  Node minHeapNode = (Node)malloc(sizeof(struct MinHeapNode));
  minHeapNode->v = v;
  minHeapNode->dist = dist;
  return minHeapNode;
}

void DecreaseKey(MinHeap H, int src, int dist)
{
  //更新目标路径长度
  int i = H->pos[src];
  H->array[i]->dist = dist;

  while (i && H->array[i]->dist < H->array[(i - 1) / 2]->dist)
  {
    H->pos[H->array[i]->v] = (i - 1) / 2;
    H->pos[H->array[(i - 1) / 2]->v] = i;
    SwapMinHeapNode(&H->array[i], &H->array[(i - 1) / 2]);
    i = (i - 1) / 2;
  }
}

void HeapifyMin(MinHeap H, int i)
{
  int smallest, left, right;
  smallest = i;
  left = 2 * i + 1;
  right = 2 * i + 2;

  if (left < H->size && H->array[left]->dist < H->array[smallest]->dist)
    smallest = left;

  if (right < H->size && H->array[right]->dist < H->array[smallest]->dist)
    smallest = right;

  if (smallest != i)
  {
    Node smallestNode = H->array[smallest];
    Node idxNode = H->array[i];

    H->pos[smallestNode->v] = i;
    H->pos[idxNode->v] = smallest;

    SwapMinHeapNode(&H->array[smallest], &H->array[i]);

    HeapifyMin(H, smallest);
  }
}

Node DeleteMin(MinHeap H)
{
  Node temp = H->array[0];
  H->array[0] = H->array[H->size - 1];

  H->size--;
  HeapifyMin(H, 0);

  return temp;
}

int isInMinHeap(MinHeap H, int v)
{
  if (H->pos[v] < H->size)
    return 1;
  return 0;
}