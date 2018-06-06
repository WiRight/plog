#include "plog.h"

// Инициализация модуля
void plogInit() {
  sem_init(&semaphore, 0, 0);
  plogFormat = "[%s] [%s] {%s} {%s} {%d}: %s";
  ptimeFormat = "%d.%m.%Y %H:%M:%S";
  pExit = 0;
  printf("[plogInit] normal\n");
  pthread_create(&logThread, NULL, threadFunc, NULL);
}

// Закрытие работы с модулем логирования
void plogDestroy() {
  pExit = 1;
  sem_post(&semaphore);
  void *threadResult;
  pthread_join(logThread, &threadResult);
  free(threadResult);
}

// Функция, которая будет в фоне работать с логами
static void *threadFunc(void *params) {
  while (1) {
    sem_wait(&semaphore);
    if (pExit) {
      printf("Try exit\n");
      pthread_exit(0);
    }
    FILE *file = fopen("log.d", "a+");

    // Get local time
    time_t lTime = time(NULL);
    struct tm *timePtr = localtime(&lTime);
    char time[80];
    strftime(time, 80, ptimeFormat, timePtr);

    char *msg = NULL;
    msg = malloc(1024 * sizeof(char));
    sprintf(msg, plogFormat,
            time,
            pLogMsg.logType,
            pLogMsg.fileName,
            pLogMsg.functionName,
            pLogMsg.line,
            pLogMsg.message
    );
    fprintf(file, "%s\n", msg);

    free(msg);
    fclose(file);
    pthread_testcancel();
  }
}

// Отправляет сообщение в поток для дальнейшей записи
void plogLog(char *logType, char *fileName, const char *functionName, int line, char *message) {
  pLogMsg.logType = logType;
  pLogMsg.fileName = fileName;
  pLogMsg.functionName = (char *) functionName;
  pLogMsg.message = message;
  pLogMsg.line = line;

  sem_post(&semaphore);
}
