#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"

<<<<<<< HEAD:src/Parser.c
void splitElements(const char *line, char ***elements, int *numElements) {
  if (!line)
    return;
  if(line[0]=='\n'||(strncmp(line, "//", 2) == 0)){
    return;
  }
  *numElements = 0;

  char *copyLine = strdup(line);
  char *tokenCount = strtok(copyLine, " ,()\n");

  while (tokenCount != NULL) {
    (*numElements)++;
=======
char **split(char *s) {
  if (!s || s[0] == '/') {
    printf("Empty input!");
    return NULL;
  }

  int tokensCounter = 0;
  char *copyS = strdup(s);
  char *tokenCount = strtok(copyS, " ,()\n");
  while (tokenCount) {
>>>>>>> upstream/master:Parser.c
    tokenCount = strtok(NULL, " ,()\n");
    tokensCounter++;
  }

  char **result = (char **)calloc(tokensCounter, sizeof(char *));
  copyS = strdup(s);
  result[0] = strtok(copyS, " ,()\n");
  for (int i = 1; i < tokensCounter; i++)
    result[i] = strtok(NULL, " ,()\n");

  return result;
}

<<<<<<< HEAD:src/Parser.c
void readFile(System * system) {
  FILE *file = fopen("input.txt", "r");
=======
// void readFile() {
//   FILE *file = fopen("input.txt", "r");
>>>>>>> upstream/master:Parser.c

//   if (file == NULL) {
//     // logErro();
//     return;
//   }

//   char line[100];

<<<<<<< HEAD:src/Parser.c
  while (fgets(line, sizeof(line), file) != NULL) {
    int numElements =0;
    char **elements;
    splitElements(line, &elements, &numElements);

    if(numElements){
      printf("chamando call function com element0: %s\n", elements[0]);
      callFunctions(elements, numElements, system);
    }

    for (int i = 0; i < numElements; i++) {
      free(elements[i]);
    }
    // free(elements);
  }
=======
//   while (fgets(line, sizeof(line), file) != NULL) {
//     int numElements;
//     char **elements;
//     splitElements(line, &elements, &numElements);

//     callFunctions(elements, numElements);

//     for (int i = 0; i < numElements; i++) {
//       free(elements[i]);
//     }
//     free(elements);
//   }
>>>>>>> upstream/master:Parser.c

//   fclose(file);
//   file = NULL;

<<<<<<< HEAD:src/Parser.c
  return;
}

void callFunctions(char **elements, int numElements, System * system) {
  FnInfo map[] = {
      {"Iniciar", 0, (ParameterType[]){TIPO_INT}, InitializeSystem},
      {"InserirAVL", 4,
       (ParameterType[]){
           TIPO_INT,
           TIPO_STRING,
           TIPO_INT,
           TIPO_STRING,
       },
       AddProcess},
      {"ListarAVL", 0, (ParameterType[]){}, ListProcessByPid},
      {"TerminarAVL", 1, (ParameterType[]){TIPO_INT}, RemoveProcess},
      {"AlterarHeap", 2, (ParameterType[]){TIPO_INT, TIPO_INT}, ChangePriority},
      {"ListarHeap", 0, (ParameterType[]){}, ListProcessByPriority},
      {"RemoverHeap", 0, (ParameterType[]){}, RemoveProcessOfMaxPriority},
      {"BloquearHash", 1, (ParameterType[]){TIPO_INT}, RemoveProcess},
  };

  for (int i = 0; i < sizeof(map) / sizeof(map[0]); ++i) {
    if (strcmp(elements[0], map[i].name) == 0) {

      if ((numElements - 1) < map[i].numParameters) {
        printf("\n A quantidade de parâmetros está incorreta.\n\n");
        return;
      }

      void **parameters = malloc((map[i].numParameters+1) * sizeof(void *));

      for (int j = 0; j < map[i].numParameters; ++j) {
        switch (map[i].parametersTypes[j]) {
        case TIPO_INT: {
          parameters[j] = malloc(sizeof(int));
          *(int *)parameters[j] = atoi(elements[j + 1]);
          break;
        }
        case TIPO_STRING: {
          parameters[j] =
              malloc(strlen(elements[j + 1]) + 1); // +1 para o caractere nulo
          strcpy((char *)parameters[j], elements[j + 1]);
          break;
        }
        }
      }

      map[i].fn(parameters, system);

      for (int j = 0; j < map[i].numParameters; ++j) {
        free(parameters[j]);
      }

      free(parameters);
      return;
    }
  }

  // logErro();
  printf("\n That function doesn't exists.\n\n");
  return;
}
=======
//   return;
// }
>>>>>>> upstream/master:Parser.c
