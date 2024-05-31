#include "HashMap.h"

typedef struct {
  HashMap *map1;
  HashMap *map2;
  HashMap *map3;
  BNode *avl;
  MaxHeap *heap;

  HashMap *functions;
} System;

// typedef struct {
//   HashMap map;
//   MaxHeap heap;
//   BNode avl;
// } System;

System *InitializeSystem();

// void *AddProcess(System sys, int pid, char *name, int priority, State state);
// void SystemProcess(System sys);
// void RemoveProcess(System sys, int pid);
// void ListProcessByPid(System sys);
// void ChangePriority(System sys, int pid, int newPriority);
// void RemoveProcessOfMaxPriority(System sys);
// void ListProcessByPriority(System sys);
// void ChangeState(System sys, int pid, State to);
// void ListProcessByState(System sys, State state);

void AddProcess(System sys, char **parameters);
void SystemProcess(System sys, char **parameters);
void RemoveProcess(System sys, char **parameters);
void ListProcessByPid(System sys, char **parameters);
void ChangePriority(System sys, char **parameters);
void RemoveProcessOfMaxPriority(System sys, char **parameters);
void ListProcessByPriority(System sys, char **parameters);
void ChangeState(System sys, char **parameters);
void ListProcessByState(System sys, char **parameters);
void FinalizeSystem(System sys, char **parameters);
