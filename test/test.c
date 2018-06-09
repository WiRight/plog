#include <stdio.h>
#include <stdlib.h>

#include <mcheck.h>

#include "lib/plog.h"

int main() {
  mtrace();
  // Инициализация потока
  plogInit();

  infoLog("Log Started");
  getchar();

  warningLog("Log Ended");
  getchar();

  // Освобождение ресурсов
  plogDestroy();
  muntrace();
  return 0;
}
