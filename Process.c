#include "Process.h"
#include <stdlib.h>

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();
  Function listFunctions[10] = {
      {"SystemProcess", SystemProcess}, {"AddProcess", AddProcess},
      //     {"RemoveProcess", RemoveProcess},
      //     {"ListProcessByPid", ListProcessByPid},
      //     {"ChangePriority", ChangePriority},
      //     {"RemoveProcessOfMaxPriority", RemoveProcessOfMaxPriority},
      //     {"ListProcessByPriority", ListProcessByPriority},
      //     {"ChangeState", ChangeState},
      //     {"ListProcessByState", ListProcessByState},
      //     {"FinalizeSystem", FinalizeSystem},
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

void AddProcess(System *sys, char **parameters) {
  char *name = parameters[0];
  int number = evalInt(parameters[1]);
  printf("AddProcess called!\n");
  printf("Parameter 0 -> %s\n", name);
  printf("Parameter 1 -> %d\n", number);
}

void SystemProcess(System *sys, char **parameters) {
  printf("SystemProcess called!\n");
}
