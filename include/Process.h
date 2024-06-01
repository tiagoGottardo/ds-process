#include "MaxHeap.h"
#include "AVLtree.h"

typedef struct {
  HashMap *map1;
  HashMap *map2;
  HashMap *map3;
  BNode *avl;
  MaxHeap *heap;

  HashMap *functions;
} System;

typedef void(Fn)(System *, char **);

typedef struct {
  char *name;
  void (*fn)(System *, char **);
} Function;

System *InitializeSystem();
void AddProcess(System *sys, char **params);
void ListAVLProcess(System *sys, char **params);
void RemoveProcess(System *sys, char **params);
void ListProcessByPid(System *sys, char **params);
void ChangePriority(System *sys, char **params);
void RemoveProcessOfMaxPriority(System *sys, char **params);
void ListProcessByPriority(System *sys, char **params);
void ChangeState(System *sys, char **params);
void ListProcessByState(System *sys, char **params);
void FinalizeSystem(System *sys, char **params);
