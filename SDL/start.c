#include "sim.h"
#include <stdio.h>

int main(void) {
  printf("start");
  simInit();
  app();
  simExit();
  return 0;
}
