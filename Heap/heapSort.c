#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b)
{
  int tempCell = *a;
  *a = *b;
  *b = tempCell;
}

void HeapifyMin(int arr[], int n, int i)
{
  int temp;
  int Child = 2 * i + 1;
  for (temp = arr[i]; 2 * i + 1 < n; i = Child)
  {
    Child = 2 * i + 1;
    if (Child < n && arr[Child] > arr[Child + 1]) //找到比较小的子元素
    {
      Child++;
    }
    if (temp > arr[Child]) //将传入的父元素和较小的子元素作比较,如果父元素较大则让子元素的值填充父元素的位置
    {
      arr[i] = arr[Child];
    }
    else
      break;
  }
  arr[i] = temp;
}

void BuildMinHeap(int arr[], int n)
{
  //从最后一个有子节点的节点开始,以此向前梳理来建成堆结构
  for (int i = (n / 2) - 1; i >= 0; --i)
  {
    HeapifyMin(arr, n, i);
  }
}

void HeapSort(int arr[], int n)
{
  BuildMinHeap(arr, n);
  for (int i = n - 1; i >= 0; --i)
  {
    Swap(&arr[0], &arr[i]);
    HeapifyMin(arr, i, 0);
  }
}

int main()
{
  int arr[] = {4, 26, 5, 87, 3, 1, 9, 18};
  int n = (sizeof(arr) / sizeof(int));
  HeapSort(arr, n);
  // BuildMinHeap(arr, n);
  for (int i = 0; i < n; ++i)
  {
    printf("%4d", arr[i]);
  }

  return 0;
}