#include "Process.h"
#include <stdlib.h>

System *InitializeSystem() {
  ;
  return NULL;
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

void AddProcess(System sys, char **parameters) {
  char *name = parameters[0];
  int number = evalInt(parameters[1]);
  printf("AddProcess called!\n");
  printf("Parameter 0 -> %s\n", name);
  printf("Parameter 1 -> %d\n", number);
}

void SystemProcess(System sys, char **parameters) {
  printf("AddProcess called!");
}
