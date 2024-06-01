#include "../include/Parser.h"
#include "../include/Process.h"

void Cli(System *sys, char *input) {
  Fn *fn;
  printf("ds-process> %s\n", input);
  // scanf(" %[^\n]", input);
  char **parameters = split(input);

  fn = (Fn *)getHashMap(sys->functions, parameters[0]);
  if (!fn) {
    printf("That command do not exists!\n");
    return;
  }
  (*fn)(sys, parameters);
}

int main() {
  System *sys = InitializeSystem();
  char input[150];
  int qtd = 5;
  char *scripts[] = {"add 0 Chrome 7 UNBLOCKED", "add 237 irefox 10 BLOCKED",
                     "ls", "clear", "ls"};

  for (int i = 0; i < qtd; i++)
    Cli(sys, scripts[i]);

  return 0;
}
