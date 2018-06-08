#include <stdio.h>
#include <stdlib.h>
#include "lib/plog.h"

int main() {
  // Инициализация потока
  plogInit();

  infoLog("Log Started");
  getchar();

  warningLog("Log Ended");
  getchar();

  // Освобождение ресурсов
  plogDestroy();
  return 0;
}
