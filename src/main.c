#include "../include/Log.h"
#include "../include/Parser.h"
#include <stdio.h>
#include <string.h>


int main() {
  initLog();
  System *sys = NULL;
  char input[150];

  while (1) {
    printf("Você quer ler de um arquivo ou continuar com a CLI? (arquivo/cli) ");
    scanf(" %[^\n]", input);
    if (!strcmp(input, "arquivo") || !strcmp(input, "cli")) {
      break;
    } else {
      printf("Você não escolheu nenhuma das opções.\n");
      continue;
    }
  }

  if (!strcmp(input, "file")) {
    while (1) {
      printf("Qual o nome do arquivo? ");
      scanf(" %[^\n]", input);
      if (ReadFile(sys, input)) break;
      
      printf("Esse arquivo não existe!\n");
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
      printf("Primeiro você precisa iniciar o sistema!\n");
    }
  }

  return 0;
}
