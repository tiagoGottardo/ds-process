#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Node *vector;
  int index;
  int capacity;
} MaxHeap;

MaxHeap *newMaxHeap();
void insertMaxHeap(MaxHeap *heap, Node *newNode);
int deleteMaxHeap(MaxHeap *heap);
void deleteByPriorityMaxHeap(MaxHeap *heap, int priority);
void printMaxHeap(MaxHeap *heap);
void deallocMaxHeap(MaxHeap *heap);
void heapify(MaxHeap *heap, int i);
