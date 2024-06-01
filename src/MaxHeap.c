#include "../include/MaxHeap.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap *newMaxHeap() {
  int capacity = 16;
  MaxHeap *heap = (MaxHeap *)calloc(1, sizeof(MaxHeap));
  heap->vector = (Node **)calloc(capacity, sizeof(Node *));

  for (int i = 0; i < capacity; i++)
    heap->vector[i] = (Node *)calloc(1, sizeof(Node));

  heap->index = 0;
  heap->capacity = capacity;
  return heap;
}

void insertHelper(MaxHeap *heap, int index) {
  int parent = (index - 1) / 2;

  if (heap->vector[parent] < heap->vector[index]) {
    Node *temp = heap->vector[parent];
    heap->vector[parent] = heap->vector[index];
    heap->vector[index] = temp;

    insertHelper(heap, parent);
  }
}

void maxHeapify(MaxHeap *heap, int index) {
  int left = index * 2 + 1;
  int right = index * 2 + 2;
  int max = index;

  if (left >= heap->index || left < 0)
    left = -1;
  if (right >= heap->index || right < 0)
    right = -1;

  if (left != -1 && heap->vector[left]->priority > heap->vector[max]->priority)
    max = left;
  if (right != -1 &&
      heap->vector[right]->priority > heap->vector[max]->priority)
    max = right;

  if (max != index) {
    Node *temp = heap->vector[max];
    heap->vector[max] = heap->vector[index];
    heap->vector[index] = temp;

    maxHeapify(heap, max);
  }
}

Node *deleteByPriorityMaxHeap(MaxHeap *heap, int from) {
  Node *deleteItem;

  if (!heap->index) {
    printf("Heap id empty.\n");
    return NULL;
  }

  for (int i = 0; i < heap->index; i++)
    if (heap->vector[i]->priority == from)
      deleteItem = heap->vector[i];

  heap->vector[0] = heap->vector[heap->index - 1];
  heap->index--;

  maxHeapify(heap, 0);
  return deleteItem;
}

Node *deleteMax(MaxHeap *heap) {
  Node *deleteItem;

  if (!heap->index) {
    printf("\nHeap id empty.");
    return NULL;
  }

  deleteItem = heap->vector[0];

  heap->vector[0] = heap->vector[heap->index - 1];
  heap->index--;

  maxHeapify(heap, 0);
  return deleteItem;
}

void insertMaxHeap(MaxHeap *heap, Node *new) {
  if (heap && heap->vector) {
    if (heap->index < heap->capacity) {
      heap->vector[heap->index] = new;
      insertHelper(heap, heap->index);
      heap->index++;
    } else {
    }
  }
}

void changePriority(MaxHeap *heap, int from, int to) {
  if (heap && heap->vector) {
    if (!heap->index) {
      printf("Heap is empty!\n");
      return;
    }
    int i = 0;
    for (i = 0; i < heap->index; i++) {
      if (from == heap->vector[i]->priority)
        break;
    }

    int root = heap->vector[0]->priority;
    heap->vector[i]->priority = to;
    maxHeapify(heap, i);
  }
}

void printMaxHeap(MaxHeap *heap) {
  if (heap && heap->vector) {
    if (!heap->index) {
      printf("Heap is empty!\n");
    } else {
      printf("Heap: \n");
      for (int i = 0; i < heap->index; i++) {
        printf("[%d] | PID: %d\t | name: %-25s\t | state: %s\t | priority: "
               "%d\n",
               i, heap->vector[i]->pid, heap->vector[i]->name,
               displayState(heap->vector[i]->state), heap->vector[i]->priority);
      }
      printf("\n");
    }
  }
}

void deallocMaxHeap(MaxHeap *heap) {
  free(heap->vector);
  free(heap);
}
