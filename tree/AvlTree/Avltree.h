#ifndef _AvlTree_H
#define _AvlTree_H

typedef struct AvlTreeNode* Node;

struct AvlTreeNode
{
    int key;
    Node left;
    Node right;
    int height;
};

int height(Node N);
Node newAvlTreeNode(int key);
Node rightRotate(Node y);
Node leftRotate(Node x);
int getBalance(Node N);
Node Insert(Node AvlTreeNode, int key);
void preOrder(Node root);

#endif //_AvlTree_H