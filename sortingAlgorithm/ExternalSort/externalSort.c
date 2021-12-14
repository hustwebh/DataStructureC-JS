#include <stdlib.h>
#include <stdio.h>

#define INT_MAX 2147483647

typedef struct MinHeapNode *Node;
typedef struct MinHeapBody *MinHeap;
struct MinHeapNode
{
    int element;
    int i; //元素的数组的索引
};

struct MinHeapBody
{
    struct MinHeapNode *harr; //指向堆中元素数组的指针
    int Size;
};

void SwapMinHeapNode(Node x, Node y)
{
    struct MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

void MinHeapify(MinHeap H, int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 1;
    int smallest = i;
    if (l < H->Size && H->harr[l].element < H->harr[i].element)
        smallest = l;
    if (r < H->Size && H->harr[r].element < H->harr[smallest].element)
        smallest = r;
    if (smallest != i)
    {
        SwapMinHeapNode(&H->harr[i], &H->harr[smallest]);
        MinHeapify(H, smallest);
    }
}

MinHeap CreateMinHeap(struct MinHeapNode a[], int size)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct MinHeapBody *));
    H->Size = size;
    H->harr = a; //存储数组地址
    int i = (H->Size - 1) / 2;
    while (i >= 0)
    {
        MinHeapify(H, i);
        i--;
    }
    return H;
}

struct MinHeapNode getMin(MinHeap H)
{
    return H->harr[0];
}

//合并两个数组,第一个是arr[l...m],第二个是arr[m+1...r]
void merge(int arr[], int l, int m, int r)
{
    int i = 0, j = 0, k = l; //三个数组,即第一个子序列,第二个子序列,合成数组三个的起点
    int n1 = m - l + 1;
    int n2 = r - m;

    /* 创建临时数组 */
    int L[n1], R[n2];

    /* 合并两子序列 */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];
}

void replaceMin(MinHeap H, struct MinHeapNode x)
{
    H->harr[0] = x;
    MinHeapify(H, 0);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {

        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

FILE *openFile(char *fileName, char *mode)
{
    FILE *fp = fopen(fileName, mode);
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

//合并文件内容,让拆分的文件块名称为0,1,2...k-1
void mergeFiles(char *output_file, int n, int k)
{
    FILE *in[k];
    for (int i = 0; i < k; i++)
    {
        char fileName[2];

        //将i转化为字符串
        snprintf(fileName, sizeof(fileName), "%d", i);

        //以读取模式打开输出文件。
        in[i] = openFile(fileName, (char *)"r");
    }

    //最终输出文件
    FILE *out = openFile(output_file, (char *)"w");

    // 创建一个具有 k 个堆节点的最小堆。 每个堆节点都有临时输出文件的第一个元素
    Node harr = (Node)malloc(k * sizeof(struct MinHeapNode));
    int i;
    for (i = 0; i < k; i++)
    {
        //如果没有输出文件为空并且索引 i 将为否，则中断
        if (fscanf(in[i], "%d ", &harr[i].element) != 1)
            break;

        //临时输出文件的索引
        harr[i].i = i;
    }

    MinHeap hp = CreateMinHeap(harr, i);

    int count = 0;

    // 现在从最小堆中一一获取最小元素并用下一个元素替换它。 运行直到所有填充的输入文件达到 EOF
    while (count != i)
    {
        // 获取最小元素并将其存储在输出文件中
        struct MinHeapNode root = getMin(hp);
        fprintf(out, "%d ", root.element);

        //找到将替换当前堆根的下一个元素。 下一个元素与当前最小元素属于同一输入文件。
        if (fscanf(in[root.i], "%d ", &root.element) != 1)
        {
            root.element = INT_MAX;
            count++;
        }

        // 用输入文件的下一个元素替换根
        replaceMin(hp, root);
    }

    for (int i = 0; i < k; i++)
        fclose(in[i]);

    fclose(out);
}

// 使用归并排序算法，创建初始运行并将它们平均分配到输出文件中
void createInitialRuns(char *input_file, int run_size, int num_ways)
{
    FILE *in = openFile(input_file, (char *)"r");

    // 输出暂存文件
    FILE *out[num_ways];
    char fileName[2];
    for (int i = 0; i < num_ways; i++)
    {
        snprintf(fileName, sizeof(fileName), "%d", i);

        out[i] = openFile(fileName, (char *)"w");
    }

// 分配一个足够大的动态数组以容纳 run_size 大小的运行
    int *arr = (int *)malloc(run_size * sizeof(int));

    int more_input = 1;
    int next_output_file = 0;

    int i;
    while (more_input)
    {
// 将 run_size 元素从输入文件写入数组
        for (i = 0; i < run_size; i++)
        {
            if (fscanf(in, "%d ", &arr[i]) != 1)
            {
                more_input = 0;
                break;
            }
        }

        // sort array using merge sort
        mergeSort(arr, 0, i - 1);

// 将记录写入适当的临时输出文件不能假设循环运行到 run_size 因为上次运行的长度可能小于 run_size
        for (int j = 0; j < i; j++)
            fprintf(out[next_output_file],
                    "%d ", arr[j]);

        next_output_file++;
    }

    for (int i = 0; i < num_ways; i++)
        fclose(out[i]);

    fclose(in);
}

void externalSort(char *input_file, char *output_file, int num_ways, int run_size)
{
// 读取输入文件，创建初始运行，并将运行分配给临时输出文件
    createInitialRuns(input_file, run_size, num_ways);

// 使用 K-way 合并暂存输出文件合并运行
    mergeFiles(output_file, run_size, num_ways);
}


int main()
{
    //拆分文件的块数
    int num_ways = 5;

    //每个文件所含数据个数
    int run_size = 100;

    char input_file[] = "input.txt";
    char output_file[] = "output.txt";

    FILE *in = openFile(input_file, (char *)"w");


    //将随机生成数写入
    for (int i = 0; i < num_ways * run_size; i++)
        fprintf(in, "%d ", rand());

    fclose(in);

    externalSort(input_file, output_file, num_ways, run_size);

    return 0;
}