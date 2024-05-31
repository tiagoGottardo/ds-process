#include "Parser.h"
#include "Process.h"

int main() {
  System *sys = InitializeSystem();
  Fn *fn;
  fn = getHashMap(sys->functions, "AddProcess");
  char *parameters[] = {"Tiago", "237"};
  (*fn)(sys, parameters);
  fn = getHashMap(sys->functions, "SystemProcess");
  (*fn)(sys, NULL);
  return 0;
}
