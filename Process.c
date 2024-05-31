#include "Process.h"
#include <stdlib.h>

void Quit() {
  printf("Program finalized!\n");
  exit(0);
}

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();
  Function listFunctions[11] = {
      {"SystemProcess", SystemProcess},
      {"AddProcess", AddProcess},
      {"RemoveProcess", RemoveProcess},
      {"ListProcessByPid", ListProcessByPid},
      {"ChangePriority", ChangePriority},
      {"RemoveProcessOfMaxPriority", RemoveProcessOfMaxPriority},
      {"ListProcessByPriority", ListProcessByPriority},
      {"ChangeState", ChangeState},
      {"ListProcessByState", ListProcessByState},
      {"FinalizeSystem", FinalizeSystem},
      {"q", Quit},
  };

  for (int i = 0; i < 11; i++)
    setHashMap(fnMap, listFunctions[i].name, listFunctions[i].fn);

  return fnMap;
};

System *InitializeSystem() {
  System *sys = (System *)calloc(1, sizeof(System));

  sys->map1 = newHashMap();
  sys->map2 = newHashMap();
  sys->map3 = newHashMap();
  sys->functions = InitializeFunctions();
  sys->avl = insertAVL(sys->avl, 34, "firefox", BLOCKED, 34);
  // it could not be hardcoded
  sys->heap = newMaxHeap();
  return sys;
}

int evalInt(char *s) {
  if (!s)
    printf("Some Error");

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
      return EXECUTING;
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

  printf("AddProcess called!\n");
  printf("Pid: %d\n", pid);
  printf("name: %s\n", name);
  printf("priority: %d\n", priority);
  printf("state: %s\n", displayState(state));
}

void SystemProcess(System *sys, char **params) {
  printf("SystemProcess called!\n");
}

void RemoveProcess(System *sys, char **params) {
  if (!checkParams(params, 1))
    return;

  int pid = evalInt(params[1]);

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

  printf("ChangePriority called!\n");
  printf("Pid: %d\n", pid);
  printf("NewPriority: %d\n", newPriority);
}

void RemoveProcessOfMaxPriority(System *sys, char **params) {
  printf("RemoveProcessOfMaxPriority called!\n");
}

void ListProcessByPriority(System *sys, char **params) {
  printf("RemoveProcessOfMaxPriority called!\n");
}

void ChangeState(System *sys, char **params) {
  if (!checkParams(params, 2))
    return;

  int pid = evalInt(params[1]);
  int to = evalInt(params[2]);

  printf("ChangePriority called!\n");
  printf("Pid: %d\n", pid);
  printf("To: %d\n", to);
}

void ListProcessByState(System *sys, char **params) {
  printf("ListProcessByPriority called!\n");
}

void FinalizeSystem(System *sys, char **params) {}
