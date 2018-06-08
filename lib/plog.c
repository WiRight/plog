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
  void* threadResult = NULL;
  pthread_join(logThread, &threadResult);
  free(threadResult);
}

// Запись в файл
static inline void writeFile(char* message) {
  FILE* file = fopen("log.d", "a+");
  fprintf(file, "%s\n", message);
  fclose(file);
}

// Получение форматированного времени
static inline char* getFormatTime() {
  time_t lTime = time(NULL);
  struct tm* timePtr = localtime(&lTime);
  char time[TIME_L] = {};
  char* result = malloc(TIME_L * sizeof(char));
  strftime(time, TIME_L, ptimeFormat, timePtr);
  strcpy(result, time);
  return result;
}

// Функция, которая будет в фоне работать с логами
static void* threadFunc(void *params) {
  while (1) {
    sem_wait(&semaphore);
    if (pExit) {
      printf("Try exit\n");
      pthread_exit(0);
    }

    char* time = getFormatTime();
    char* msg = malloc(1024 * sizeof(char));

    sprintf(msg, plogFormat,
            time,
            pLogMsg.logType,
            pLogMsg.fileName,
            pLogMsg.functionName,
            pLogMsg.line,
            pLogMsg.message
    );

    writeFile(msg);
    free(msg);
    pthread_testcancel();
  }
}

// Отправляет сообщение в поток для дальнейшей записи
void plogLog(char* logType, char* fileName, const char* functionName, int line, char* message) {
  pLogMsg.logType = logType;
  pLogMsg.fileName = fileName;
  pLogMsg.functionName = (char *) functionName;
  pLogMsg.message = message;
  pLogMsg.line = line;

  sem_post(&semaphore);
}
