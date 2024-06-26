#include "../include/AVLtree.h"
#include "../include/Log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DicioState diciostate[] = {
    {"BLOQUEADO", BLOCKED}, {"PRONTO", READY}, {"EXECUCAO", EXECUTING}};

State evalState(char *s) {
  for (int i = 0; diciostate[i].name; i++)
    if (!strcmp(diciostate[i].name, s))
      return diciostate[i].val;

  printf("[ERRO]: Estado não existe\n");
  logMessage("log/AVL.txt", "[ERRO]: Estado não existe");
  return UNKNOWN;
}

void AVLlog(const char *text) {}

int height(BNode *bnode) {
  if (!bnode)
    return 0;
  return bnode->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

Node *newNode(int pid, char *name, State state, int priority) {
  Node *node = (Node *)calloc(1, sizeof(Node));
  if (!node) {
    logMessage("log/AVL.txt", "[ERRO]: Não doi possivel alocar memória em newNode");
    return NULL;
  }
  node->name = (char *)calloc(strlen(name) + 1, sizeof(char));

  strcpy(node->name, name);
  node->pid = pid;
  node->state = state;
  node->priority = priority;

  logMessage("log/AVL.txt", "Processo criado com PID: %d", pid);

  return node;
}

BNode *newBNode(int pid, Node *node) {
  BNode *bnode = (BNode *)calloc(1, sizeof(BNode));
  if (!bnode) {
    logMessage("log/AVL.txt", "[ERRO]: Não doi possível alocar memória em newBNode");
    return NULL;
  }

  bnode->node = node;
  bnode->key = pid;
  bnode->height = 1;

  return bnode;
}

BNode *rightRotate(BNode *y) {
  BNode *x = y->left;
  BNode *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

BNode *leftRotate(BNode *x) {
  BNode *y = x->right;
  BNode *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

int getBalance(BNode *bnode) {
  if (!bnode)
    return 0;
  return height(bnode->left) - height(bnode->right);
}

BNode *insertAVL(BNode *bnode, int key, Node *node) {
  if (!bnode)
    return (newBNode(key, node));

  if (key < bnode->key)
    bnode->left = insertAVL(bnode->left, key, node);
  else if (key > bnode->key)
    bnode->right = insertAVL(bnode->right, key, node);
  else {
    logMessage("log/AVL.txt", "A process with that pid already exists!");
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
  for (int i = 0; i < (sizeof(diciostate) / sizeof(diciostate[0])); i++) {
    if (diciostate[i].val == state) {
      return diciostate[i].name;
    }
  }

  return "BLOCKED";
}

BNode *minValueNode(BNode *bnode) {
  BNode *current = bnode;

  while (current->left)
    current = current->left;

  return current;
}
void deallocNode(Node **node) {
  free((*node)->name);
  free(*node);
  *node = NULL;
}

void deallocBNode(BNode **bnode) {
  free(*bnode);
  *bnode = NULL;
}

BNode *deleteAVL(BNode *root, int key) {
  if (!root)
    return NULL;

  if (key < root->key)
    root->left = deleteAVL(root->left, key);

  else if (key > root->key)
    root->right = deleteAVL(root->right, key);

  else {
    logMessage("log/AVL.txt", "Desalocando processo com PID: %d", key);
    if (!root->left || !root->right) {
      BNode *temp = root->left ? root->left : root->right;

      if (!temp) {
        temp = root;
        deallocNode(&root->node);
        root = NULL;
      } else {
        root->node = temp->node;
        root->left = temp->left;
        root->right = temp->right;
        root->key = temp->key;
      }

      deallocBNode(&temp);
    } else {
      BNode *temp = minValueNode(root->right);

      deallocNode(&root->node);
      temp->left = root->left;
      root = temp;

      root->right = deleteAVL(root->right, temp->key);
    }
  }

  if (!root)
    return NULL;

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
    
    logMessage("log/AVL.txt", "O processo com PID: %d não foi encontrado", pid);
    return NULL;
  }

  if (pid > root->key) {
    return searchAVL(root->right, pid);
  } else if (pid < root->key) {
    return searchAVL(root->left, pid);
  } else {
    logMessage("log/AVL.txt", "A busca por PID: %d econtrou processo com sucesso", pid);
    return root->node;
  }
}

void deallocAllTree(BNode **bnode) {
  logMessage("log/AVL.txt", "Desalocando arvore");
  if (*bnode) {
    deallocAllTree(&(*bnode)->right);
    deallocAllTree(&(*bnode)->left);
    deallocNode(&(*bnode)->node);
    deallocBNode(bnode);
  }
}

void preOrder(BNode *root, void(fn)(Node *node)) {
  if (root) {
    preOrder(root->left, fn);
    fn(root->node);
    preOrder(root->right, fn);
  }
}
