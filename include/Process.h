typedef struct System System;
typedef struct State State;

// typedef struct {
//   HashMap map;
//   MaxHeap heap;
//   BNode avl;
// } System;

System *InitializeSystem();

void *AddProcess(int pid, char *name, int priority, State state);
void SystemProcess();
void RemoveProcess(int pid);
void ListProcessByPid();
void ChangePriority(int pid, int newPriority);
void RemoveProcessOfMaxPriority();
void ListProcessByPriority();
void ChangeState(int pid, State to);
void ListProcessByState(State state);

void FinalizeSystem();
