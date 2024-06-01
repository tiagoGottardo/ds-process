#include "../include/Process.h"
#include <stdlib.h>

void Clear() { system("clear"); }

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();
  Function listFunctions[10] = {{"add", AddProcess},
                                {"list", ListAVLProcess},
                                {"remove", RemoveProcess},
                                {"changePriority", ChangePriority},
                                {"removePriority", RemoveProcessOfMaxPriority},
                                {"listByPriority", ListProcessByPriority},
                                {"changeState", ChangeState},
                                {"listByState", ListProcessByState},
                                {"q", FinalizeSystem},
                                {"clear", Clear}};

  for (int i = 0; i < 10; i++)
    setHashMap(fnMap, listFunctions[i].name, listFunctions[i].fn);

  return fnMap;
};

System *InitializeSystem() {
  System *sys = (System *)calloc(1, sizeof(System));

  sys->map1 = newHashMap();
  sys->map2 = newHashMap();
  sys->map3 = newHashMap();
  sys->functions = InitializeFunctions();

  // it could not be hardcoded
  sys->heap = newMaxHeap();
  return sys;
}

int evalInt(char *s) {
  if (!s)
    printf("Params not found!");

  int result = atoi(s);
  if (!result && s[0] != '0')
    printf("%s is not a number\n", s);

  return result;
}

// not finished
State evalState(char *s) {
  char *states[3] = {"EXECUTING", "BLOCKED", "UNBLOCKED"};
  for (int i = 0; i < 3; i++) {
    if (!strcmp(states[i], s)) {
      return BLOCKED;
    }
  }
  return BLOCKED;
}

bool checkParams(char **params, int num) {
  for (int i = 1; i <= num; i++)
    if (!params[i]) {
      printf("We need more params\n");
      return false;
    }

  return true;
}

void AddProcess(System *sys, char **params) {
  if (!checkParams(params, 4))
    return;

  int pid = evalInt(params[1]);
  char *name = params[2];
  int priority = evalInt(params[3]);
  State state = evalState(params[4]);

  Node *node = newNode(pid, name, state, priority);

  sys->avl = insertAVL(sys->avl, pid, node);
  setHashMap(sys->map1, node->name, node);
  setHashMap(sys->map2, node->name, node);
  setHashMap(sys->map3, node->name, node);
  insertMaxHeap(sys->heap, node);

  printf("AddProcess called!\n");
  printf("Pid: %d\n", pid);
  printf("name: %s\n", name);
  printf("priority: %d\n", priority);
  printf("state: %s\n", displayState(state));
}

void ListAVLProcess(System *sys, char **params) {
  if (!sys->avl)
    printf("Nothing here yet!\n");
  else
    preOrder(sys->avl, printProcess);
  printf("ListProcess called!\n");
}

void RemoveProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);

  Node *node = searchAVL(sys->avl, pid);
  if (node) {
    setHashMap(sys->map1, node->name, NULL);
    setHashMap(sys->map2, node->name, NULL);
    setHashMap(sys->map3, node->name, NULL);
    deleteByPriorityMaxHeap(sys->heap, node->priority);
    sys->avl = deleteAVL(sys->avl, node->pid);
  }

  printf("RemoveProcess called!\n");
  printf("Pid: %d\n", pid);
}

void ListProcessByPid(System *sys, char **params) {
  printf("ListProcessByPid called!\n");
}

void ChangePriority(System *sys, char **params) {
  if (!checkParams(params, 2))
    return;

  int pid = evalInt(params[1]);
  int newPriority = evalInt(params[2]);

  Node *node = searchAVL(sys->avl, pid);
  if (node) {
    deleteByPriorityMaxHeap(sys->heap, node->priority);
    node->priority = newPriority;
    insertMaxHeap(sys->heap, node);
  } else {
    printf("Process not found!");
  }

  printf("ChangePriority called!\n");
  printf("Pid: %d\n", pid);
  printf("NewPriority: %d\n", newPriority);
}

void RemoveProcessOfMaxPriority(System *sys, char **params) {
  deleteMaxHeap(sys->heap);
  printf("RemoveProcessOfMaxPriority called!\n");
}

void ListProcessByPriority(System *sys, char **params) {
  printMaxHeap(sys->heap);
  printf("RemoveProcessOfMaxPriority called!\n");
}

void ChangeState(System *sys, char **params) {
  if (!checkParams(params, 2))
    return;

  int pid = evalInt(params[1]);
  int to = evalState(params[2]);

  Node *node = searchAVL(sys->avl, pid);
  node->state = to;

  printf("ChangePriority called!\n");
  printf("Pid: %d\n", pid);
  printf("To: %d\n", to);
}

void ListProcessByState(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  State state = evalState(params[1]);

  showHashMapByState(sys->map1, state);
  printf("ListProcessByPriority called!\n");
}

void FinalizeSystem(System *sys, char **params) {
  deallocAllTree(&sys->avl);
  deallocHashMap(sys->map1);
  deallocHashMap(sys->map2);
  deallocHashMap(sys->map3);
  deallocMaxHeap(sys->heap);
  printf("Program finalized!\n");

  exit(0);
}
