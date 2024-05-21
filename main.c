#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum State { BLOCKED, UNBLOCKED, EXECUTING } State;

typedef struct Node {
  char name[50];
  State state;
  int priority;
} Node;

typedef struct BNode {
  int pid;
  Node *node;
  struct BNode *right;
  struct BNode *left;
  int height;
} BNode;

int height(struct BNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

Node *newNode(char *name, State state) {
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (!node) {
    printf("Error on alloc memory of node!");
    return NULL;
  }

  strcpy(node->name, name);
  node->state = state;

  return node;
}

BNode *newBNode(int pid, char *name, State state) {
  BNode *bnode = (BNode *)calloc(1, sizeof(BNode));
  if (!bnode) {
    printf("Error on alloc memory of bnode!");
    return NULL;
  }

  Node *node = newNode(name, state);

  bnode->node = node;
  bnode->pid = pid;
  bnode->height = 1;

  return bnode;
}

struct BNode *rightRotate(struct BNode *y) {
  struct BNode *x = y->left;
  struct BNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

struct BNode *leftRotate(struct BNode *x) {
  struct BNode *y = x->right;
  struct BNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(struct BNode *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct BNode *insert(struct BNode *node, int pid, char *name, State state) {
  if (node == NULL)
    return (newBNode(pid, name, state));

  if (pid < node->pid)
    node->left = insert(node->left, pid, name, state);
  else if (pid > node->pid)
    node->right = insert(node->right, pid, name, state);
  else {
    printf("That PID already exists!");
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);

  if (balance > 1 && pid < node->left->pid)
    return rightRotate(node);

  if (balance < -1 && pid > node->right->pid)
    return leftRotate(node);

  if (balance > 1 && pid > node->left->pid) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && pid < node->right->pid) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

char *displayState(State state) {
  switch (state) {
  case BLOCKED:
    return "BLOCKED";
  case UNBLOCKED:
    return "UBLOCKED";
  case EXECUTING:
    return "EXECUTING";
  }
}

void preOrder(struct BNode *root) {
  if (root != NULL) {
    printf("PID: %d\t | name: %s\t\t\t | state: %s\t | priority: %d\n",
           root->pid, root->node->name, displayState(root->node->state),
           root->node->priority);
    preOrder(root->left);
    preOrder(root->right);
  }
}

int main() {
  BNode *node = NULL;
  node = insert(node, 123, "Word", BLOCKED);
  node = insert(node, 2342, "Excel", EXECUTING);

  preOrder(node);

  printf("\n");
  return 0;
}
