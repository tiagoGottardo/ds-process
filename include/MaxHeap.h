<<<<<<< HEAD:include/MaxHeap.h
#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "AVLtree.h"
=======
#include "HashMap.h"
>>>>>>> upstream/master:MaxHeap.h
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
void printMaxHeap(MaxHeap *heap);
void deallocMaxHeap(MaxHeap *heap);
void heapify(MaxHeap *heap, int i);

#endif

