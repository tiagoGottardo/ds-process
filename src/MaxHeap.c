#include "../include/MaxHeap.h"
#include <stdio.h>
#include <stdlib.h>

void swap(Node *v1, Node *v2) {
  Node *aux = v1;
  v1 = v2;
  v2 = aux;
}

void heapify(MaxHeap *heap, int i) {
  int highest = i;
  int leftChild = 2 * i;
  int rightChild = 2 * i + 1;

  if (leftChild <= heap->index && rightChild <= heap->index) {
    if (heap->vector[leftChild]->priority > heap->vector[highest]->priority &&
        heap->vector[leftChild]->priority >
            heap->vector[rightChild]->priority) {
      highest = leftChild;
    } else if (heap->vector[rightChild]->priority >
                   heap->vector[highest]->priority &&
               heap->vector[rightChild]->priority >
                   heap->vector[leftChild]->priority) {
      highest = rightChild;
    }
  } else if (leftChild <= heap->index && heap->vector[leftChild]->priority >
                                             heap->vector[highest]->priority) {
    highest = leftChild;
  } else if (rightChild <= heap->index && heap->vector[rightChild]->priority >
                                              heap->vector[highest]->priority) {
    highest = rightChild;
  }
  if (highest != i) {
    swap(heap->vector[i], heap->vector[highest]);
    heapify(heap, highest);
  }
}

MaxHeap *newMaxHeap() {
  int capacity = 16;
  MaxHeap *heap = (MaxHeap *)malloc(sizeof(MaxHeap));
  heap->vector = (Node **)malloc(capacity * sizeof(Node *));
  for (int i = 0; i < capacity; i++) {
    heap->vector[i] = (Node *)calloc(1, sizeof(Node));
  }
  heap->index = 0;
  heap->capacity = capacity;
  return heap;
}

void insertMaxHeap(MaxHeap *heap, Node *new) {
  if (heap && heap->vector) {

    if (!heap->index) {
      heap->vector[0] = (Node *)malloc(sizeof(Node));

      heap->vector[0] = new;
      heap->index++;
      return;
    }

    if (heap->index == heap->capacity) {
      Node *vet = realloc(heap->vector, heap->capacity * 2);

      if (vet) {
        heap->vector[0] = vet;
      } else {
        printf("Heap is full! It could not possible insert anymore.\n");
        return;
      }
    }

    heap->index++;
    int i = heap->index;
    heap->vector[i] = new;
    int parent = i / 2;

    while (i > 1 &&
           heap->vector[i]->priority > heap->vector[parent]->priority) {
      swap(heap->vector[i], heap->vector[parent]);
      i = parent;
      parent = i / 2;
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
    heapify(heap, i);
  }
}

void deleteByPriorityMaxHeap(MaxHeap *heap, int priority) {
  if (heap && heap->vector) {
    if (!heap->index) {
      printf("Heap is empty!\n");
      return;
    }
    int i = 0;
    for (i = 0; i < heap->index; i++) {
      if (priority == heap->vector[i]->priority)
        break;
    }

    int root = heap->vector[0]->priority;
    heap->vector[i] = heap->vector[heap->index - 1];
    heap->index--;
    heapify(heap, i);
  }
}

int deleteMaxHeap(MaxHeap *heap) {
  if (heap && heap->vector) {
    if (!heap->index) {
      printf("Heap is empty!\n");
      return -1;
    }

    int root = heap->vector[0]->priority;
    heap->vector[0] = heap->vector[heap->index - 1];
    heap->index--;
    heapify(heap, 1);
    return root;
  }
  return -1;
}

void printMaxHeap(MaxHeap *heap) {
  if (heap && heap->vector) {
    if (!heap->index) {
      printf("Heap is empty!\n");
    } else {
      printf("Heap: \n");
      for (int i = 0; i < heap->index; i++) {
        printf(
            "[%d] | PID: %d\t | name: %-25s\t | state: %s\t | priority: %d\n",
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
