#include "AVLtree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Node *vector;
  int index;
  int capacity;
} MaxHeap;

MaxHeap *newMaxHeap(int capacity);
void insertMaxHeap(MaxHeap *heap, Node *newNode);
int deleteMaxHeap(MaxHeap *heap);
void printMaxHeap(MaxHeap *heap);
void deallocMaxHeap(MaxHeap *heap);
