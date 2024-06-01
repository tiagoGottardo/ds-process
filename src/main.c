#include "../include/Parser.h"
#include "../include/Process.h"

int main() {
  System *sys = InitializeSystem();
  char input[150];
  Fn *fn;

  while (1) {
    printf("ds-process> ");
    scanf(" %[^\n]", input);
    char **parameters = split(input);

    fn = (Fn *)getHashMap(sys->functions, parameters[0]);
    if (!fn) {
      printf("That command do not exists!\n");
      continue;
    }
    (*fn)(sys, parameters);
    free(parameters);
  }
  return 0;
}
