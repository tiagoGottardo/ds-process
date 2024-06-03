#include "../include/Process.h"
#include "../include/Log.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *s) {
  if(s[0] == '\n'){
    return NULL;
  };
  if (!s) {
    printf("Empty input!\n");
    return NULL;
  }
  if (s[0] == '/') {
    printf("Just a comment!\n");
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
        printf("System initialize\n");
      } else {
      printf("You need to initiate system before do anything!\n");
      }
      continue;
    }

    fn = (Fn *)getHashMap(sys->functions, parameters[0], true, true);
    if (!fn) {
      printf("That command do not exists!\n");
      free(parameters[0]);
      free(parameters);
      continue;
    }
    logMessage("log/log.txt", "Chamando função: %s", parameters[0]);
    (*fn)(sys, parameters);
    free(parameters[0]);
    free(parameters);
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
      free(parameters[0]);
      free(parameters);
      printf("That command do not exists!\n");
      continue;
    }
    logMessage("log/log.txt", "Chamando função: %s", parameters[0]);
    (*fn)(sys, parameters);
    free(parameters[0]);
    free(parameters);
  }
}
