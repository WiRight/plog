#include <stdlib.h>
#include <stdio.h>
#include "plog.h"

int main() {
  plogInit();

  printf("%s\n", "start");
  plogLog("start");  
  getchar();
  plogLog("WiRighr");
  getchar();
  
  plogLog("Reader");
  getchar();
  
  printf("%s\n", "end");
  plogLog("end");

  plogDestroy();
  return 0;
}
