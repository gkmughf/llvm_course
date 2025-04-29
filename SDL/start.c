#include "gfv.h"
#include <stdio.h>

int main(void) {
  printf("start");
  gfvInit();
  app();
  gfvExit();
  return 0;
}
