#ifndef MAIN_H
#define MAIN_H

#include "Parser.h"
#include "HashMap.h"
#include "MaxHeap.h"
#include "AVLtree.h"

typedef struct System{
  HashMap *map;
  MaxHeap *heap;
  BNode *avl;
} System;

#endif