#include "HashMap.h"

typedef struct {
  Node **vector;
  int index;
  int capacity;
} MaxHeap;

MaxHeap *newMaxHeap();
void insertMaxHeap(MaxHeap *heap, Node *newNode);
Node *deleteMaxHeap(MaxHeap *heap, int priority);
void printMaxHeap(MaxHeap *heap);
void deallocMaxHeap(MaxHeap *heap);
