#include "Parser.h"
#include "Process.h"
typedef void(Fn)(System, char **);

typedef struct {
  char *name;
  void (*fn)(System, char **);
} Function;

HashMap *InitializeFunctions() {
  HashMap *fnMap = newHashMap();

  Function listFunctions[10] = {{"AddProcess", AddProcess},
                                {"SystemProcess", SystemProcess}};

  for (int i = 0; i < 10; i++)
    setHashMap(fnMap, listFunctions[i].name, listFunctions[i].fn);

  return fnMap;
};

int main() {
  HashMap *functions = InitializeFunctions();
  System sys;
  char *parameters[] = {"Tiago", "0tiago"};
  Fn *fn = (Fn *)getHashMap(functions, "AddProcess");
  (*fn)(sys, parameters);

  return 0;
}
