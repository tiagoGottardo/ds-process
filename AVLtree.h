#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum State { BLOCKED, UNBLOCKED, EXECUTING } State;
typedef struct Node {
  int pid;
  char name[50];
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

int height(struct BNode *N);
int max(int a, int b);
Node *newNode(int pid, char *name, State state, int priority);
BNode *newBNode(int pid, char *name, State state, int priority);
BNode *rightRotate(struct BNode *y);
BNode *leftRotate(struct BNode *x);
int getBalance(struct BNode *N);
BNode *insertAVL(struct BNode *node, int key, char *name, State state,
                 int priority);
char *displayState(State state);
BNode *minValueNode(struct BNode *node);
void deallocBNode(BNode **bnode);
BNode *deleteAVL(struct BNode *root, int key);
Node *searchAVL(BNode *root, int pid);
void deallocAllTree(BNode **node);
void printNode(Node *node);
void preOrder(BNode *root, void(fn)(Node *node));
