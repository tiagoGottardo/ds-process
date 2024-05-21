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

int height(struct BNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

Node *newNode(int pid, char *name, State state) {
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (!node) {
    printf("Error on alloc memory of node!");
    return NULL;
  }

  strcpy(node->name, name);
  node->pid = pid;
  node->state = state;

  return node;
}

BNode *newBNode(int pid, char *name, State state) {
  BNode *bnode = (BNode *)calloc(1, sizeof(BNode));
  if (!bnode) {
    printf("Error on alloc memory of bnode!\n");
    return NULL;
  }

  Node *node = newNode(pid, name, state);

  bnode->node = node;
  bnode->key = pid;
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

BNode *insertBNode(struct BNode *node, int key, char *name, State state) {
  if (node == NULL)
    return (newBNode(key, name, state));

  if (key < node->key)
    node->left = insertBNode(node->left, key, name, state);
  else if (key > node->key)
    node->right = insertBNode(node->right, key, name, state);
  else {
    printf("That key already exists!\n");
    return node;
  }

  node->height = 1 + max(height(node->left), height(node->right));

  int balance = getBalance(node);

  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
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

BNode *minValueNode(struct BNode *node) {
  struct BNode *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

void deallocBNode(BNode **bnode) {
  free((*bnode)->node);
  free(*bnode);
}

BNode *deleteBNode(struct BNode *root, int key) {

  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteBNode(root->left, key);

  else if (key > root->key)
    root->right = deleteBNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct BNode *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;

      deallocBNode(&temp);
    } else {

      BNode *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteBNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);

  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

void deallocAllTree(BNode *node) {
  if (node) {
    deallocAllTree(node->right);
    deallocAllTree(node->left);
    deallocBNode(&node);
  }
}

void printNode(Node *node) {
  printf("PID: %d\t | name: %s\t\t\t | state: %s\t | priority: %d\n", node->pid,
         node->name, displayState(node->state), node->priority);
}

void preOrder(BNode *root, void(fn)(Node *node)) {
  if (root != NULL) {
    fn(root->node);
    preOrder(root->left, fn);
    preOrder(root->right, fn);
  }
}

int main() {
  BNode *node = NULL;
  node = insertBNode(node, 123, "Word", BLOCKED);
  node = insertBNode(node, 2342, "Excel", EXECUTING);
  Node *newRef;
  if (!(newRef = searchAVL(node, 12))) {
    deallocAllTree(node);
    return 0;
  }

  printNode(newRef);

  preOrder(node, printNode);

  return 0;
}
