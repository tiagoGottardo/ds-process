#include "../include/MaxHeap.h"
#include <stdio.h>
#include <stdlib.h>

MaxHeap *newMaxHeap() {
  int capacity = INITIAL_CAPACITY;
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

  if (heap->vector[parent]->priority < heap->vector[index]->priority) {
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

Node *deleteMaxHeap(MaxHeap *heap, int pid) {
  Node *deleteItem;

  if (!heap->index) {
    printf("Heap id empty.\n");
    return NULL;
  }

  int i;
  for (i = 0; i < heap->index; i++)
    if (heap->vector[i]->pid == pid) {
      deleteItem = heap->vector[i];
      break;
    }

  heap->vector[i] = heap->vector[heap->index - 1];
  heap->index--;

  maxHeapify(heap, 0);
  return deleteItem;
}

void insertMaxHeap(MaxHeap *heap, Node *new) {
  if (heap) {
    if (heap->index < heap->capacity) {
      heap->vector[heap->index] = new;
      insertHelper(heap, heap->index++);
    } else {

      printf("DOBRANDO max heap");

      int newCapacity = heap->capacity * 2;
      Node **newVector = (Node **)malloc(newCapacity * sizeof(Node *));

      if (newVector) {
        // Copia os elementos existentes para o novo vetor
        memcpy(newVector, heap->vector, heap->capacity * sizeof(Node *));

        // Libera o vetor antigo e aponta o heap para o novo vetor
        free(heap->vector);
        heap->vector = newVector;
        heap->capacity = newCapacity;

        // Insere o novo elemento
        heap->vector[heap->index] = new;
        insertHelper(heap, heap->index++);
      } else {
        printf("ERRO ao dobrar tamanho do heap");
      }
    }
  }
}

void printMaxHeap(MaxHeap *heap) {
  if (heap && heap->vector)
    for (int i = 0; i < (heap->index); i++)
      printProcess(heap->vector[i]);
}

void deallocMaxHeap(MaxHeap *heap) {
  free(heap->vector);
  free(heap);
}
