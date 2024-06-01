#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Node **vector;
  int index;
  int capacity;
} MaxHeap;

MaxHeap *newMaxHeap();
void insertMaxHeap(MaxHeap *heap, Node *newNode);
Node *deleteMaxHeap(MaxHeap *heap);
Node *deleteByPriorityMaxHeap(MaxHeap *heap, int from);
void printMaxHeap(MaxHeap *heap);
void deallocMaxHeap(MaxHeap *heap);
