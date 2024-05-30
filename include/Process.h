#include "state.h"

typedef struct System System;

// typedef struct {
//   HashMap map;
//   MaxHeap heap;
//   BNode avl;
// } System;

void InitializeSystem(System * system);

void AddProcess(int pid, char *name, int priority, State state, System * system);
void SystemProcess(System * system);
void RemoveProcess(int pid,System * system);
void ListProcessByPid(System * system);
void ChangePriority(int pid, int newPriority, System * system);
void RemoveProcessOfMaxPriority(System * system);
void ListProcessByPriority(System * system);
void ChangeState(int pid, State to, System * system);
void ListProcessByState(State state, System * system);

void FinalizeSystem(System * system);
