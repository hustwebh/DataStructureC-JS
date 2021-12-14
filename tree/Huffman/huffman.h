#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#define MaxCapacity 30

typedef struct node *Node;
typedef struct MinHeapBody *MinHeap;

struct node
{
  char data;
  int frequency;
  struct node *LeftChild;
  struct node *RightChild;
};

struct MinHeapBody
{
  int size;
  Node Array[MaxCapacity];
};

Node newNode(char charecter, int frequency);
void PrintCodes(Node root, int arr[], int top);
void SwapMinHeapNode(Node *a, Node *b);
void HeapifyMin(MinHeap H, int i);
Node DeleteMin(MinHeap H);
void insertMinHeap(MinHeap H, Node node);
void BuildMinHeap(MinHeap H);
MinHeap createMinHeap(char data[], int frequency[], int size);
Node BuildHuffmanTree(char data[], int frequency[], int size);
void HuffmanCodes(char data[], int freq[], int size);
void PrintArr(int arr[], int n);

#endif