#include "Process.h"

void InitializeSystem(System * system){

    system->map = newHashMap();
    system->heap = newMaxHeap(100);
    system->avl = NULL;

    printf("Sistema Iniciado :)\n");

    return;
}

void AddProcess(int pid, char *name, int priority, State state, System * system){return;}
void SystemProcess(System * system){return;}
void RemoveProcess(int pid,System * system){return;}
void ListProcessByPid(System * system){return;}
void ChangePriority(int pid, int newPriority, System * system){return;}
void RemoveProcessOfMaxPriority(System * system){return;}
void ListProcessByPriority(System * system){return;}
void ChangeState(int pid, State to, System * system){return;}
void ListProcessByState(State state, System * system){return;}

void FinalizeSystem(System * system){return;}