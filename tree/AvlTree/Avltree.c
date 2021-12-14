#include<stdio.h>
#include<stdlib.h>
#include"Avltree.h"
 
int max(int a, int b)
{
    return (a > b)? a : b;
} 

int height(Node N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 

Node newAvlTreeNode(int key)
{
    Node AvlTreeNode = (Node)malloc(sizeof(struct AvlTreeNode));
    AvlTreeNode->key   = key;
    AvlTreeNode->left   = NULL;
    AvlTreeNode->right  = NULL;
    AvlTreeNode->height = 1;
    return(AvlTreeNode);
}
 

Node rightRotate(Node y)
{
    Node x = y->left;
    Node T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// 一个用于左旋转以 x 为根的子树的实用函数
Node leftRotate(Node x)
{
    Node y = x->right;
    Node T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// 获取AvlTreeNode N的平衡因子
int getBalance(Node N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// 在以 AvlTreeNode 为根的子树中插入键并返回子树的新根的递归函数.
Node Insert(Node AvlTreeNode, int key)
{
    if (AvlTreeNode == NULL)
        return(newAvlTreeNode(key));
 
    if (key < AvlTreeNode->key)
        AvlTreeNode->left  = Insert(AvlTreeNode->left, key);
    else if (key > AvlTreeNode->key)
        AvlTreeNode->right = Insert(AvlTreeNode->right, key);
    else
        return AvlTreeNode;
 
    /* 2. 更新这个祖先 AvlTreeNode 的高度 */
    AvlTreeNode->height = 1 + max(height(AvlTreeNode->left),height(AvlTreeNode->right));
 
    /* 3. 获取这个祖先的平衡因子AvlTreeNode 检查这个 AvlTreeNode 是否变成不平衡*/
    int balance = getBalance(AvlTreeNode);
 
 
    //左儿子的左子树  
    if (balance > 1 && key < AvlTreeNode->left->key)
        return rightRotate(AvlTreeNode);
 
    //右儿子的右子树 
    if (balance < -1 && key > AvlTreeNode->right->key)
        return leftRotate(AvlTreeNode);
 
    //左儿子的右子树 
    if (balance > 1 && key > AvlTreeNode->left->key)
    {
        AvlTreeNode->left =  leftRotate(AvlTreeNode->left);
        return rightRotate(AvlTreeNode);
    }
 
    //右儿子的左子树 
    if (balance < -1 && key < AvlTreeNode->right->key)
    {
        AvlTreeNode->right = rightRotate(AvlTreeNode->right);
        return leftRotate(AvlTreeNode);
    }
 
    return AvlTreeNode;
}
 
void preOrder(Node root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
