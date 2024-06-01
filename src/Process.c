#include "../include/Process.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Clear(System *sys, char **params) { system("clear"); }

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();
  Function listFunctions[10] = {
      {"add", AddProcess},
      {"ls", ListAVLProcess},
      {"rm", RemoveProcess},
      {"cgp", ChangePriority},
      {"rmp", RemoveProcessOfMaxPriority},
      {"ltp", ListProcessByPriority},
      {"cgs", ChangeState},
      {"lss", ListProcessByState},
      {"q", FinalizeSystem},
      {"clear", Clear},
  };

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
  if (result <= 0) {
    printf("Just positive numbers!\n");
    result = 0;
  }

  return result;
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
  if (!pid || !priority || state == UNKNOWN)
    return;

  Node *node = newNode(pid, name, state, priority);

  sys->avl = insertAVL(sys->avl, pid, node);
  setHashMap(sys->map1, node->name, node);
  setHashMap(sys->map2, node->name, node);
  setHashMap(sys->map3, node->name, node);
  insertMaxHeap(sys->heap, node);
}

void ListAVLProcess(System *sys, char **params) {
  if (!sys->avl)
    printf("Nothing here yet!\n");
  else {
    printf("----------------------------------------------- Process List "
           "-----------------------------------------------\n");
    preOrder(sys->avl, printProcess);
    printf("----------------------------------------------------------------"
           "-------------"
           "---------------------"
           "----------\n");
  }
}

void RemoveProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);
  if (!pid)
    return;

  Node *node = searchAVL(sys->avl, pid);
  if (node) {
    deleteHashMap(sys->map1, node->name);
    deleteHashMap(sys->map2, node->name);
    deleteHashMap(sys->map3, node->name);
    deleteByPriorityMaxHeap(sys->heap, node->priority);
    sys->avl = deleteAVL(sys->avl, node->pid);
  } else {
    printf("Process not found!\n");
  }
}

void ChangePriority(System *sys, char **params) {
  if (!checkParams(params, 2))
    return;

  int pid = evalInt(params[1]);
  int newPriority = evalInt(params[2]);
  if (!pid || !newPriority)
    return;

  Node *node = searchAVL(sys->avl, pid);
  if (node) {
    deleteByPriorityMaxHeap(sys->heap, node->priority);
    node->priority = newPriority;
    insertMaxHeap(sys->heap, node);
  } else {
    printf("Process not found!");
  }
}

void RemoveProcessOfMaxPriority(System *sys, char **params) {
  Node *node = searchAVL(sys->avl, sys->heap->vector[0]->pid);
  if (node) {
    deleteHashMap(sys->map1, node->name);
    deleteHashMap(sys->map2, node->name);
    deleteHashMap(sys->map3, node->name);
    deleteByPriorityMaxHeap(sys->heap, 0);
    sys->avl = deleteAVL(sys->avl, node->pid);
  } else {
    printf("Process not found!");
  }
}

void ListProcessByPriority(System *sys, char **params) {
  if (!sys->heap->index)
    printf("Nothing here yet!\n");
  else {
    printf("----------------------------------------------- Process List "
           "-----------------------------------------------\n");
    printMaxHeap(sys->heap);
    printf("----------------------------------------------------------------"
           "-------------"
           "---------------------"
           "----------\n");
  }
}

void ChangeState(System *sys, char **params) {
  if (!checkParams(params, 2))
    return;

  int pid = evalInt(params[1]);
  int to = evalState(params[2]);
  if (!pid || !to)
    return;

  Node *node = searchAVL(sys->avl, pid);
  if (!node) {
    printf("Process not found!");
    return;
  }
  node->state = to;
}

void ListProcessByState(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;
  State state = evalState(params[1]);
  if (state == UNKNOWN)
    return;

  if (!sys->map1->length) {
    printf("Nothing here yet!\n");
    return;
  }
  printf("----------------------------------------------- Process List "
         "-----------------------------------------------\n");
  showHashMapByState(sys->map1, state);
  printf("----------------------------------------------------------------"
         "-------------"
         "---------------------"
         "----------\n");
}

void FinalizeSystem(System *sys, char **params) {
  deallocHashMap(sys->map1);
  deallocHashMap(sys->map2);
  deallocHashMap(sys->map3);
  deallocMaxHeap(sys->heap);
  deallocAllTree(&sys->avl);
  free(params);
  
  printf("Program finalized!\n");
  exit(0);
}
