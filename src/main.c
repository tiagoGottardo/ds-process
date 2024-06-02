#include "../include/Log.h"
#include "../include/Parser.h"
#include <stdio.h>
#include <string.h>

int main() {
  initLog();
  System *sys = NULL;
  char input[150];

  while (1) {
    printf("Do you want to read a file or continue with CLI? (file/cli) ");
    scanf(" %[^\n]", input);
    if (!strcmp(input, "file") || !strcmp(input, "cli")) {
      break;
    } else {
      printf("You don't chose none of options.\n");
      continue;
    }
  }

  if (!strcmp(input, "file")) {
    while (1) {
      printf("What's file name? ");
      scanf(" %[^\n]", input);
      if (ReadFile(sys, input)) break;
      
      printf("That file not exists!\n");
      continue;
      }
  } else {
    while (1) {
      printf("dsprocess> ");
      scanf(" %[^\n]", input);
      if (!strcmp(input, "Iniciar")) {
        sys = InitializeSystem();
        Cli(sys);
        break;
      }
      printf("You need to initiate system before do anything!\n");
    }
  }

  return 0;
}
