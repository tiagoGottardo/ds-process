#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum State { BLOCKED, READY, EXECUTING, UNKNOWN } State;

typedef struct {
  char *name;
  State val;
} DicioState;

typedef struct Node {
  int pid;
  char *name;
  State state;
  int priority;
} Node;

typedef struct BNode {
  int key;
  Node *node;
  struct BNode *right;
  struct BNode *left;
  int height;
} BNode;

State evalState(char *s);
int height(BNode *N);
int max(int a, int b);
Node *newNode(int pid, char *name, State state, int priority);
// BNode *newBNode(int pid, Node *node);
// BNode *rightRotate(BNode *y);
// BNode *leftRotate(BNode *x);
// int getBalance(BNode *N);
BNode *insertAVL(BNode *bnode, int key, Node *node);
char *displayState(State state);
// BNode *minValueNode(BNode *node);
// void deallocBNode(BNode **bnode);
BNode *deleteAVL(BNode *root, int key);
Node *searchAVL(BNode *root, int pid);
void deallocAllTree(BNode **node);
// void printNode(Node *node);
void preOrder(BNode *root, void(fn)(Node *node));

#endif
