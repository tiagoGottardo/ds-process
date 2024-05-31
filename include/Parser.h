<<<<<<< HEAD:include/Parser.h
#ifndef PARSER_H
#define PARSER_H

#include "Process.h"

=======
>>>>>>> upstream/master:Parser.h
typedef enum { TIPO_INT, TIPO_STRING } ParameterType;

typedef struct {
  char name[20];
  int numParameters;
  ParameterType *parametersTypes;
  void (*fn)();
} FnInfo;

<<<<<<< HEAD:include/Parser.h
void callFunctions(char **elementos, int numElementos, System * system);
void readFile(System * system);
void separaelementos();
void SeparaElementos(const char *linha, char ***elementos, int *numElementos);

#endif

=======
char **split(char *s);
// void callFunctions(char **elementos, int numElementos);
// void readFile();
// void separaelementos();
// void SeparaElementos(const char *linha, char ***elementos, int
// *numElementos);
>>>>>>> upstream/master:Parser.h
