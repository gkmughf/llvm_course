#include <stdio.h>

void instructionLogger(char *instructionName, char *operandName) {
  printf("%s <- %s\n", instructionName, operandName);
}
