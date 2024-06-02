#include "../include/Process.h"
#include "../include/Log.h"
#include <stdio.h>
#include <stdlib.h>

void Clear(System *sys, char **params) { system("clear"); }

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();
  Function listFunctions[14] = {
      {"InserirAVL", AddProcess},          {"ListarAVL", ListAVLProcess},
      {"TerminarAVL", RemoveProcess},      {"Terminar", RemoveProcess},
      {"AlterarHeap", ChangePriority},     {"BloquearHash", BlockProcess},
      {"DesbloquearHash", UnblockProcess}, {"RemoverHash", RemoveProcess},
      {"ListaHeap", ListProcessByPriority}, {"RemoverHeap", RemoveProcessOfMaxPriority},
      {"ListarHash", ListProcessByState},  {"Executar", ExecuteProcess},
      {"Encerrar", FinalizeSystem},        {"clear", Clear},
  };

  for (int i = 0; i < 14; i++)
    setHashMap(fnMap, listFunctions[i].name, listFunctions[i].fn, true, true);

  return fnMap;
};

System *InitializeSystem() {
  logMessage("log/log.txt", "Iniciando sistema");
  System *sys = (System *)calloc(1, sizeof(System));

  logMessage("log/hash1.txt", "Iniciando hashmap/quadraticFnv");
  sys->quadraticFnv = newHashMap();
  logMessage("log/hash2.txt", "Iniciando hashmap/linearFnv");
  sys->linearFnv = newHashMap();
  logMessage("log/hash3.txt", "Iniciando hashmap/linearDjb2");
  sys->linearDjb2 = newHashMap();
  sys->functions = InitializeFunctions();

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

void BlockProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);
  if (!pid)
    return;

  ChangeState(sys, pid, BLOCKED);
  return;
}

void ExecuteProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);
  if (!pid)
    return;

  ChangeState(sys, pid, EXECUTING);
  return;
}

void UnblockProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);
  if (!pid)
    return;

  ChangeState(sys, pid, READY);
  return;
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

  Node *search = searchAVL(sys->avl, pid);

  if (search) {
    printf("A process with that pid already exists!\n");
    return;
  }

  Node *node = newNode(pid, name, state, priority);

  sys->avl = insertAVL(sys->avl, pid, node);
  setHashMap(sys->quadraticFnv, node->name, node, true, false);
  setHashMap(sys->linearFnv, node->name, node, true, true);
  setHashMap(sys->linearDjb2, node->name, node, false, true);
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
    deleteHashMap(sys->quadraticFnv, node->name, true, false);
    deleteHashMap(sys->linearFnv, node->name, true, true);
    deleteHashMap(sys->linearDjb2, node->name, false, true);
    deleteMaxHeap(sys->heap, node->priority);
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
    deleteMaxHeap(sys->heap, node->priority);
    node->priority = newPriority;
    insertMaxHeap(sys->heap, node);
  } else {
    printf("Process not found!\n");
  }
}

void RemoveProcessOfMaxPriority(System *sys, char **params) {
  Node *node = searchAVL(sys->avl, sys->heap->vector[0]->pid);
  if (node) {
    deleteHashMap(sys->quadraticFnv, node->name, true, false);
    deleteHashMap(sys->linearFnv, node->name, true, true);
    deleteHashMap(sys->linearDjb2, node->name, false, true);
    deleteMaxHeap(sys->heap, node->priority);
    sys->avl = deleteAVL(sys->avl, node->pid);
  } else {
    printf("Process not found!\n");
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

void ChangeState(System *sys, int pid, State state) {
  Node *node = searchAVL(sys->avl, pid);
  if (!node) {
    printf("Process not found!\n");
    return;
  }
  node->state = state;
}

void ListProcessByState(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;
  State state = evalState(params[1]);
  if (state == UNKNOWN)
    return;

  if (!sys->quadraticFnv->length) {
    printf("Nothing here yet!\n");
    return;
  }
  printf("----------------------------------------------- Process List "
         "-----------------------------------------------\n");
  showHashMapByState(sys->quadraticFnv, state);
  printf("----------------------------------------------------------------"
         "-------------"
         "---------------------"
         "----------\n");
}

void FinalizeSystem(System *sys, char **params) {
  deallocHashMap(sys->quadraticFnv);
  deallocHashMap(sys->linearFnv);
  deallocHashMap(sys->linearDjb2);
  deallocMaxHeap(sys->heap);
  deallocAllTree(&sys->avl);
  free(params);

  printf("Program finalized!\n");
  exit(0);
}
