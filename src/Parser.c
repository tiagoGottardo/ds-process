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
