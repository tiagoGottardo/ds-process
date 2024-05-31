typedef enum { TIPO_INT, TIPO_STRING } ParameterType;

typedef struct {
  char name[20];
  int numParameters;
  ParameterType *parametersTypes;
  void (*fn)();
} FnInfo;

char **split(char *s);
// void callFunctions(char **elementos, int numElementos);
// void readFile();
// void separaelementos();
// void SeparaElementos(const char *linha, char ***elementos, int
// *numElementos);
