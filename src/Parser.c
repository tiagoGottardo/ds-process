#include "../include/Process.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *s) {
  if(s[0] == '\n'){
    return NULL;
  };
  if (!s) {
    printf("Input vazio!\n");
    return NULL;
  }
  if (s[0] == '/') {
    printf("Apenas um comentário!\n");
    return NULL;
  }

  int tokensCounter = 0;
  char *copyS = strdup(s);
  char *tokenCount = strtok(copyS, " ,()\n");
  while (tokenCount) {
    tokenCount = strtok(NULL, " ,()\n");
    tokensCounter++;
  }

  free(copyS);

  char **result = (char **)calloc(tokensCounter, sizeof(char *));
  char *copyS2 = strdup(s);
  result[0] = strtok(copyS2, " ,()\n");
  for (int i = 1; i < tokensCounter; i++)
    result[i] = strtok(NULL, " ,()\n");

  return result;
}

bool ReadFile(System *sys, char *filename) {
  FILE *file = fopen(filename, "r");

  if (!file)
    return false;

  char line[150];
  char**parameters;
  Fn *fn;
  while (fgets(line, sizeof(line), file)) {
    printf("%s", line);
    if(line[0] == '\n') continue;
    parameters = split(line);

    if (!parameters)
      continue;

    if(sys == NULL){
      if(!strcmp(parameters[0], "Iniciar")){
        sys = InitializeSystem();
        printf("Sistema inicializado\n");
      } else {
      printf("Primeiro você precisa iniciar o sistema!\n");
      }
      continue;
    }

    fn = (Fn *)getHashMap(sys->functions, parameters[0], true, true);
    if (!fn) {
      printf("Isso não é um comando válido!\n");
      continue;
    }
    (*fn)(sys, parameters);
    printf("\n");
  }

  fclose(file);
  file = NULL;

  return true;
}

void Cli(System *sys) {
  Fn *fn;
  char input[150];
  while (1) {
    printf("ds-process> ");
    scanf(" %[^\n]", input);

    char **parameters = split(input);
    if (!parameters)
      continue;

    fn = (Fn *)getHashMap(sys->functions, parameters[0], true, true);
    if (!fn) {
      printf("Isso não é um comando válido!\n");
      continue;
    }
    (*fn)(sys, parameters);
  }
}
