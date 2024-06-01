#include "../include/AVLtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DicioState diciostate[] = {
    {"BLOCKED", BLOCKED},
    {"UNBLOCKED", UNBLOCKED},
    {"EXECUTING", EXECUTING}
};

State evalState(char *s) {

  for (int i = 0; diciostate[i].name != NULL; i++) {
    if (strcmp(diciostate[i].name, s) == 0) {
      return diciostate[i].val;
    }
  }
  
  return BLOCKED;
}

int height(struct BNode *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

Node *newNode(int pid, char *name, State state, int priority) {
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (!node) {
    printf("Error on alloc memory of node!");
    return NULL;
  }
  node->name = (char *)calloc(strlen(name)+1, sizeof(char));// Adiciona 1 para o caractere nulo

  strcpy(node->name, name);
  node->pid = pid;
  node->state = state;
  node->priority = priority;

  return node;
}

BNode *newBNode(int pid, Node *node) {
  BNode *bnode = (BNode *)calloc(1, sizeof(BNode));
  if (!bnode) {
    printf("Error on alloc memory of bnode!\n");
    return NULL;
  }

  bnode->node = node;
  bnode->key = pid;
  bnode->height = 1;

  return bnode;
}

BNode *rightRotate(BNode *y) {
  struct BNode *x = y->left;
  struct BNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

BNode *leftRotate(BNode *x) {
  struct BNode *y = x->right;
  struct BNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(BNode *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

BNode *insertAVL(BNode *bnode, int key, Node *node) {
  if (bnode == NULL)
    return (newBNode(key, node));

  if (key < bnode->key)
    bnode->left = insertAVL(bnode->left, key, node);
  else if (key > bnode->key)
    bnode->right = insertAVL(bnode->right, key, node);
  else {
    printf("That key already exists!\n");
    return bnode;
  }

  bnode->height = 1 + max(height(bnode->left), height(bnode->right));

  int balance = getBalance(bnode);

  if (balance > 1 && key < bnode->left->key)
    return rightRotate(bnode);

  if (balance < -1 && key > bnode->right->key)
    return leftRotate(bnode);

  if (balance > 1 && key > bnode->left->key) {
    bnode->left = leftRotate(bnode->left);
    return rightRotate(bnode);
  }

  if (balance < -1 && key < bnode->right->key) {
    bnode->right = rightRotate(bnode->right);
    return leftRotate(bnode);
  }

  return bnode;
}

char *displayState(State state) {
  for (int i = 0; i<(sizeof(diciostate)/sizeof(diciostate[0])); i++) {
    if (diciostate[i].val == state) {
      return diciostate[i].name;
    }
  }
  
  return "BLOCKED";
}

BNode *minValueNode(BNode *node) {
  struct BNode *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

void deallocBNode(BNode **bnode) {
  free((*bnode)->node);
  (*bnode)->node = NULL;
  free(*bnode);
  *bnode = NULL;
}

BNode *deleteAVL(struct BNode *root, int key) {

  if (!root)
    return root;

  if (key < root->key)
    root->left = deleteAVL(root->left, key);

  else if (key > root->key)
    root->right = deleteAVL(root->right, key);

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

      root->right = deleteAVL(root->right, temp->key);
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

Node *searchAVL(BNode *root, int pid) {
  if (!root) {
    printf("Process not found in AVL Tree!\n");
    return NULL;
  }

  if (pid > root->key) {
    return searchAVL(root->right, pid);
  } else if (pid < root->key) {
    return searchAVL(root->left, pid);
  } else {
    return root->node;
  }
}

void deallocAllTree(BNode **node) {
  if (*node) {
    deallocAllTree(&(*node)->right);
    deallocAllTree(&(*node)->left);
    deallocBNode(node);
  }
}

void preOrder(BNode *root, void(fn)(Node *node)) {
  if (root) {
    fn(root->node);
    preOrder(root->left, fn);
    preOrder(root->right, fn);
  }
}
