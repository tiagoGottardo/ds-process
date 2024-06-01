#include "../include/Parser.h"
#include "../include/Process.h"
#include <stdio.h>

void Cli(System *sys, char *input) {
  Fn *fn;
  printf("ds-process> %s\n", input);
  // scanf(" %[^\n]", input);
  char **parameters = split(input);
  if (!parameters)
    return;

  fn = (Fn *)getHashMap(sys->functions, parameters[0]);
  if (!fn) {
    printf("That command do not exists!\n");
    return;
  }
  (*fn)(sys, parameters);
}

int main() {
  System *sys = InitializeSystem();
  char input[150];
  printf("======================== Init =========================\n");
  char *scripts[] = {
      "add 1 Chrome 7 READY",
      "ls",
      "add 1 VisualStudioCode 9 EXECUTING",
      "rm 1",
      "ltp",
      "add 43 Alacritty 10 EXECUTING",
      "add 44 Nautilus 6 EXECUTING",
      "ls",
      "rm 41",
      "rm 43",
      "ls",
      "add 45 Docker 5 EXECUTING",
      "add 46 Obsidian 9 BLOCKED",
      "rm 45",
      "ls",
      "add 237 Firefox 15 BLOCKED",
      "ls",
      "rm 0",
      "something 12 12",
      "//something",
      "cgp 44 100",
      "ltp",
      "cgp 44 5",
      "rmp",
      "ltp",
      "cgs 44 EXECUTING",
      "lss EXECUTING",
      "q",
  };

  for (int i = 0; true; i++)
    Cli(sys, scripts[i]);

  return 0;
}
