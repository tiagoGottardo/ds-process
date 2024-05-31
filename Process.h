#include "MaxHeap.h"

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
void SystemProcess(System *sys, char **params);
void RemoveProcess(System *sys, char **params);
void ListProcessByPid(System *sys, char **params);
void ChangePriority(System *sys, char **params);
void RemoveProcessOfMaxPriority(System *sys, char **params);
void ListProcessByPriority(System *sys, char **params);
void ChangeState(System *sys, char **params);
void ListProcessByState(System *sys, char **params);
void FinalizeSystem(System *sys, char **params);

// void *AddProcess(System sys, int pid, char *name, int priority, State state);
// void SystemProcess(System sys);
// void RemoveProcess(System sys, int pid);
// void ListProcessByPid(System sys);
// void ChangePriority(System sys, int pid, int newPriority);
// void RemoveProcessOfMaxPriority(System sys);
// void ListProcessByPriority(System sys);
// void ChangeState(System sys, int pid, State to);
// void ListProcessByState(System sys, State state);
