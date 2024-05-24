#include "MaxHeap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  BNode *node = NULL;
  MaxHeap *heap = newMaxHeap(10);
  node = insertAVL(node, 123, "Word", BLOCKED, 10);
  node = insertAVL(node, 2342, "Excel", EXECUTING, 2);

  // if (!(newRef = searchAVL(node, 12))) {
  //   deallocAllTree(&node);
  //   return 0;
  // }

  // preOrder(node, printNode);
  printMaxHeap(heap);
  printf("\n");

  // preOrder(node, printNode);

  return 0;
}
