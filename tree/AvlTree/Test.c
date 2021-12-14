#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Avltree.h"

#define MAXSIZE 100

int main()
{
  int arr[MAXSIZE];
  int n = 30;
  Node root = NULL;
  srand((unsigned)time(NULL));
  for (int i = 0; i < n; i++)
  {
    arr[i] = rand() % 100 + 1;
  }
  printf("随机输入的数据:");
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
    root = Insert(root,arr[i]);
  }

  printf("\n先序遍历生成的AVL树为 \n");
  preOrder(root);

  return 0;
}