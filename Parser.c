#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Parser.h"

char **split(char *s) {
  if (!s || s[0] == '/') {
    printf("Empty input!");
    return NULL;
  }

  int tokensCounter = 0;
  char *copyS = strdup(s);
  char *tokenCount = strtok(copyS, " ,()\n");
  while (tokenCount) {
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

// void readFile() {
//   FILE *file = fopen("input.txt", "r");

//   if (file == NULL) {
//     // logErro();
//     return;
//   }

//   char line[100];

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

//   fclose(file);
//   file = NULL;

//   return;
// }

// void callFunctions(char **elements, int numElements) {
//   FnInfo map[] = {
//       {"Iniciar", 1, (ParameterType[]){TIPO_INT}, InitializeSystem},
//       {"InserirAVL", 4,
//        (ParameterType[]){
//            TIPO_INT,
//            TIPO_STRING,
//            TIPO_INT,
//            TIPO_STRING,
//        },
//        AddProcess},
//       {"ListarAVL", 0, (ParameterType[]){}, ListProcessByPid},
//       {"TerminarAVL", 1, (ParameterType[]){TIPO_INT}, RemoveProcess},
//       {"AlterarHeap", 2, (ParameterType[]){TIPO_INT, TIPO_INT},
//       ChangePriority},
//       {"ListarHeap", 0, (ParameterType[]){}, ListProcessByPriority},
//       {"RemoverHeap", 0, (ParameterType[]){}, RemoveProcessOfMaxPriority},
//       {"BloquearHash", 1, (ParameterType[]){TIPO_INT}, RemoveProcess},
//   };

//   for (int i = 0; i < sizeof(map) / sizeof(map[0]); ++i) {
//     if (strcmp(elements[0], map[i].name) == 0) {

//       if ((numElements - 1) < map[i].numParameters) {
//         printf("\n A quantidade de parâmetros está incorreta.\n\n");
//         return;
//       }

//       void **parameters = malloc(map[i].numParameters * sizeof(void *));

//       for (int j = 0; j < map[i].numParameters; ++j) {
//         switch (map[i].parametersTypes[j]) {
//         case TIPO_INT: {
//           parameters[j] = malloc(sizeof(int));
//           *(int *)parameters[j] = atoi(elements[j + 1]);
//           break;
//         }
//         case TIPO_STRING: {
//           parameters[j] =
//               malloc(strlen(elements[j + 1]) + 1); // +1 para o caractere
//               nulo
//           strcpy((char *)parameters[j], elements[j + 1]);
//           break;
//         }
//         }
//       }

//       map[i].fn(parameters);

//       for (int j = 0; j < map[i].numParameters; ++j) {
//         free(parameters[j]);
//       }

//       free(parameters);
//       return;
//     }
//   }

//   // logErro();
//   printf("\n That function doesn't exists.\n\n");
//   return;
// }
