#include "../include/Parser.h"
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

void TestsLoop(System *sys, char *input) {
  Fn *fn;
  printf(ANSI_COLOR_RED "ds-process> %s\n" ANSI_COLOR_RESET, input);
  char **parameters = split(input);
  if (!parameters)
    return;

  fn = (Fn *)getHashMap(sys->functions, parameters[0], true, true);
  if (!fn) {
    printf("That command do not exists!\n");
    return;
  }
  (*fn)(sys, parameters);
}

int main() {
  System *sys = InitializeSystem();
  char input[150];
  printf("======================== Init Tests =========================\n");
  char *scripts[] = {
      "add 1 Chrome 7 READY",
      "ls",
      "add 1 VisualStudioCode 9 EXECUTING",
      "rm 1",
      "ltp",
      "cgs 44 EXECUTING",
      "lss EXECUTING",
      "add 1 Chrome 7 READY",
      "add 2 Chrome 7 READY",
      "add 3 Chrome 7 READY",
      "add 4 Chrome 7 READY",
      "add 5 Chrome 7 READY",
      "add 6 Chrome 7 READY",
      "add 7 Chrome 7 READY",
      "add 8 Chrome 7 READY",
      "add 9 Chrome 7 READY",
      "add 10 Chrome 7 READY",
      "add 11 Chrome 7 READY",
      "add 12 Chrome 7 READY",
      "add 13 Chrome 7 READY",
      "add 14 Chrome 7 READY",
      "add 15 Chrome 7 READY",
      "add 16 Chrome 7 READY",
      "add 17 Chrome 7 READY",
      "add 18 Chrome 7 READY",
      "add 19 Chrome 7 READY",
      "add 20 Chrome 7 READY",
      "ltp",
      "q",
  };

  for (int i = 0; true; i++)
    TestsLoop(sys, scripts[i]);

  return 0;
}
