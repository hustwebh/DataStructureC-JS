#include <stdio.h>
#include <stdlib.h>
#include"huffman.h"

#define MaxCapacity 30

Node newNode(char charecter, int frequency)
{
  Node p = (Node)malloc(sizeof(struct node));
  p->data = charecter;
  p->frequency = frequency;
  p->LeftChild = p->RightChild = NULL;

  return p;
}

void PrintArr(int arr[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf("%d", arr[i]);

  printf("\n");
}


void PrintCodes(Node root, int arr[], int top)
{

  if (root->LeftChild)
  {
    arr[top] = 0;
    PrintCodes(root->LeftChild, arr, top + 1);
  }

  if (root->RightChild)
  {
    arr[top] = 1;
    PrintCodes(root->RightChild, arr, top + 1);
  }

  if (!(root->LeftChild) && !(root->RightChild))
  {

    printf("%c: ", root->data);
    PrintArr(arr, top);
  }
}

void SwapMinHeapNode(Node *a, Node *b)
{

  Node t = *a;
  *a = *b;
  *b = t;
}

void HeapifyMin(MinHeap H, int i)
{
  int min = i;
  int LChild = 2 * i + 1, RChild = 2 * i + 2;

  if (LChild < H->size && H->Array[LChild]->frequency > H->Array[min]->frequency)
    min = LChild;
  if (RChild < H->size && H->Array[RChild]->frequency > H->Array[min]->frequency)
    min = RChild;
  if (min != i)
  {
    SwapMinHeapNode(&H->Array[min], &H->Array[i]);
    HeapifyMin(H, min);
  }
}

Node DeleteMin(MinHeap H)
{
  Node temp = H->Array[0];
  H->Array[0] = H->Array[H->size - 1];

  H->size--;
  HeapifyMin(H, 0);

  return temp;
}

void insertMinHeap(MinHeap H, Node node)
{
  ++H->size;
  int i = H->size - 1;
  while (i && node->frequency < H->Array[(i - 1) / 2]->frequency)
  {
    H->Array[i] = H->Array[(i - 1) / 2];
    i = (i - 1) / 2;
  }

  H->Array[i] = node;
}

void BuildMinHeap(MinHeap H)
{
  int n = H->size - 1;

  for (int i = (n / 2) - 1; i >= 0; --i)
  {
    HeapifyMin(H, i);
  }
}

MinHeap createMinHeap(char data[], int frequency[], int size)
{

  MinHeap minHeap= (MinHeap)malloc(sizeof(struct MinHeapBody));

  minHeap->size = size;

  for (int i = 0; i < size; ++i)
    minHeap->Array[i] = newNode(data[i], frequency[i]);

  BuildMinHeap(minHeap);

  return minHeap;
}

Node BuildHuffmanTree(char data[], int frequency[], int size)
{
  MinHeap H = createMinHeap(data, frequency, size);
  Node Left, Right, Top;
  while (H->size > 1)
  {
    Left = DeleteMin(H);
    Right = DeleteMin(H);

    Top = newNode('$', Left->frequency + Right->frequency);

    Top->LeftChild = Left;
    Top->RightChild = Right;

    insertMinHeap(H, Top);
  }

  return DeleteMin(H);
}

void HuffmanCodes(char data[], int freq[], int size)
{
  Node root = BuildHuffmanTree(data, freq, size);

  int arr[MaxCapacity], top = 0;

  PrintCodes(root, arr, top);
}

int main()
{

  char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
  int freq[] = {5, 9, 12, 13, 16, 45};

  int size = sizeof(arr) / sizeof(arr[0]);

  HuffmanCodes(arr, freq, size);

  return 0;
}