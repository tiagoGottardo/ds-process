#ifndef PARSER_H
#define PARSER_H

#include "Process.h"

typedef enum { TIPO_INT, TIPO_STRING } ParameterType;

typedef struct {
  char name[20];
  int numParameters;
  ParameterType *parametersTypes;
  void (*fn)();
} FnInfo;

void callFunctions(char **elementos, int numElementos, System * system);
void readFile(System * system);
void separaelementos();
void SeparaElementos(const char *linha, char ***elementos, int *numElementos);

#endif

